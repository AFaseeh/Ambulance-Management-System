#ifndef RECORDS_H
#define RECORDS_H
#include<string>void Organiser::generateoutputfile() {
	int epc = 0;
	int npc = 0;
	int sumwaitTime = 0;
	int rcount = 0;  // Keep track of the actual record count
	int spc = 0;
	Car* c1 = nullptr;
	int countcars=0;
	int busytime=0;


	// Open output file
	ofstream myfile("outputfile.txt");
	if (!myfile.is_open()) {
		cerr << "Error: Could not open output file!" << endl;
		return;
	}
	cout << "Output file written successfully." << endl;

	// Write header to the file
	myfile << "FT   PID    QT     WT    STATUS\n";

	NPatientQueue tempPatients;
	OutCarsPriQueue tempCars;

	Patient* p1 = nullptr;
	record* arr[100];  
	int recordCount = 0; 

	while (AllPatients.dequeue(p1)) {
		Car* assignedCar = nullptr;
		int travelTime = 0;
		int finishTime = 0;
		int waitTime = 0;

		string status = "SERVED";

		// Count patients based on type
		switch (p1->GetType()) {
		case NP:
			npc++;
			break;
		case SP:
			spc++;
			break;
		case EP:
			epc++;
			break;
		}

		// Find the assigned car
		int x;
		while (OutCars.dequeue(c1, x)) {
			tempCars.enqueue(c1, x);  
			if (c1 && c1->GetAssignedPatientID() == p1->GetID()) {
				busytime = 
				
				assignedCar = c1;
				break;
			}
		}

		if (assignedCar != nullptr) {
			travelTime = static_cast<int>(p1->getDistance()) / assignedCar->GetSpeed();
			finishTime = p1->GetPickUpTime() + travelTime;
			waitTime = p1->GetPickUpTime() - p1->GetRequestTime();
			sumwaitTime += waitTime;

			arr[recordCount] = new record(finishTime, p1->GetID(), p1->GetRequestTime(), waitTime, status);
			recordCount++;
		}
		else {
			status = "NO CAR";  // No record if no car was assigned
		}

		// Restore cars back to the queue
		while (!tempCars.isEmpty()) {
			tempCars.dequeue(c1, x);
			OutCars.enqueue(c1, x);
		}

		// Check for cancel requests
		CancelRequest* cancelReq = nullptr;
		CancelledRequest.dequeue(cancelReq);
		if (cancelReq != nullptr && cancelReq->getPID() == p1->GetID()) {
			status = "CANCELED";
		}
		else if (cancelReq != nullptr) {
			CancelledRequest.enqueue(cancelReq);
		}

		tempPatients.enqueue(p1);
	}

	sortrecords(arr, recordCount);

	// Write the sorted records to the output file
	for (int i = 0; i < recordCount; i++) {
		if (arr[i] != nullptr) {  
			myfile << arr[i]->getFT() << "   "
				<< arr[i]->getPID() << "    "
				<< arr[i]->getQT() << "    "
				<< arr[i]->getWT() << "    "
				<< arr[i]->getStatus() << "\n";
		}
	}

	// Restore patients back to the original queue
	while (!tempPatients.isEmpty()) {
		tempPatients.dequeue(p1);
		AllPatients.enqueue(p1);
	}

	myfile << "patients:" << AllPatients.getCount() << "   "
		<< "[NP: " << npc << ", " << "SP: " << spc << ", " << "EP: " << epc << "]\n";
	myfile << "hospitals:" << hospitalNumber << '\n';
	myfile << "Avg wait Time:" << (sumwaitTime / AllPatients.getCount()) << '\n';
	myfile << "\n\n";

#include <iostream>

class record {

	private:
            double FT;
            int PID;
            int QT;
            double WT;
            std::string status;
            static int count;

public:
    record(double ft = 0, int pid = 0, int qt = 0, double wt = 0, std::string status = "");

    double getFT()   const;
    int getPID() const;
    int getQT() const;
    double getWT() const;
    std::string getStatus() const;
    static const int getcount();
    static void setcount(int x);
    


    
};
#endif

