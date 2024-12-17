#include "../headers/Organiser.h"
//#include "../headers/Hospital.h"
//#include "../headers/Patient.h"
//#include "../headers/Car.h"
#include "../headers/CancelRequest.h"
#include <iostream>
#include <string>
using namespace std;

Organiser::Organiser()
	: numOfRequests(-1), hospitals(nullptr), hospitalNumber(-1), distanceMatrix(nullptr)
{
	ui = new UI;
}

Organiser::~Organiser() {
	for (int i = 0; i < hospitalNumber; ++i) {
		delete hospitals[i];
		delete[] distanceMatrix[i];
	}
	delete[] hospitals;
	delete[] distanceMatrix;

	for (int i = 0; i < numOfRequests; i++)
	{
		Patient* p = nullptr;
		AllPatients.dequeue(p);
		if (p)
			delete p;
	}
}


void Organiser::UpdateTimeStep(int time)
{
	for (int i = 0; i < hospitalNumber; i++) {
		int random = rand() % 100 + 1;
		string message;
		bool done = true;
		if (random >= 91 && random < 95) {
			//move car from back to free list of its hospital
			message = "Move From Back to free ";
			returnCar(time);
			if (done)
			{
				message = message + "\n";
			}
			else
				message = message + "(No available car)\n";
		}
		else if (random >= 80 && random < 90) {
			//move car from out to back list
			message = "Move from Out to Back ";
			SwitchOutToBack(time);
			if (done)
			{
				message = message + "\n";
			}
			else
				message = message + "(No available car)\n";
		}
		else if (random >= 70 && random < 75) {
			// take a patient from all patients and assign to car 

			message = "Moving NCar from hospital[" + std::to_string(i) + "] to out list CID: ";
			Car* free = hospitals[i]->OutCar(CAR_TYPE::NORMAL_CAR);
			if (free)
			{
				message = message + std::to_string(free->GetCarID()) + "\n";
				OutCars.enqueue(free, 0);
			}
			else
			{
				message = message + "No available car\n";
			}
		}
		else if (random >= 40 && random < 45) {
			//same as above but for special car
			message = "Moving SCar from hospital[" + std::to_string(i) + "] to out list CID: ";
			Car* free = hospitals[i]->OutCar(CAR_TYPE::SPECIAL_CAR);
			if (free)
			{
				message = message + std::to_string(free->GetCarID()) + "\n";
				OutCars.enqueue(free, 0);
			}
			else
			{
				message = message + "No available car\n";
			}
		}
		else if (random >= 30 && random < 40) {
			//move NP patient to finished
			message = "Moving NP from hospital[" + std::to_string(i) + "] to finish list PID: ";
			Patient* free = hospitals[i]->FinishNP();
			if (free)
			{
				message = message + std::to_string(free->GetID()) + "\n";
				FinishedRequest.enqueue(free);
			}
			else
			{
				message = message + "No available Patient\n";
			}
		}
		else if (random >= 20 && random < 25)
		{
			//move EP patient to finished
			message = "Moving EP from hospital[" + std::to_string(i) + "] to finish list PID: ";
			Patient* free = hospitals[i]->FinishEP();
			if (free)
			{
				message = message + std::to_string(free->GetID()) + "\n";
				FinishedRequest.enqueue(free);
			}
			else
			{
				message = message + "No available Patient\n";
			}
		}
		else if (random >= 10 && random < 20) {
			//move SP patient to finished
			message = "Moving SP from hospital[" + std::to_string(i) + "] to finish list PID: ";
			Patient* free = hospitals[i]->FinishSP();
			if (free)
			{
				message = message + std::to_string(free->GetID()) + "\n";
				FinishedRequest.enqueue(free);
			}
			else
			{
				message = message + "No available Patient\n";
			}
		}

		ui->PrintTimeStep(this, time, hospitals[i], message);


		if (FinishedRequest.getCount() == numOfRequests)
		{
			ui->PrintMessage("Finished Simulation");
			return;
		}
	}
}


void Organiser::LoadFile()
{
	string fname = ui->Loadfile();

	cout << fname << endl;

	ifstream fin(fname);
	if (fin.is_open() == false)
	{
		ui->Error("Error: Can't load, couldn't open File");
		return;
	}

	// Loading Hospitals
	fin >> hospitalNumber;
	hospitals = new Hospital * [hospitalNumber];
	for (int i = 0; i < hospitalNumber; i++) {
		hospitals[i] = new Hospital(this, i);
	}

	// Loading Speed of Cars
	int speedSC, speedNC;
	fin >> speedSC >> speedNC;
	Car::SetStaticSpeedNC(speedNC);
	Car::SetStaticSpeedSC(speedSC);

	// Distance Matrix of size (hospitalNum * hospitalNum)
	distanceMatrix = new int* [hospitalNumber];
	for (int i = 0; i < hospitalNumber; i++) {
		distanceMatrix[i] = new int[hospitalNumber];
	}
	for (int i = 0; i < hospitalNumber; i++)
	{
		for (int j = 0; j < hospitalNumber; j++)
		{
			fin >> distanceMatrix[i][j];
		}
	}

	// Loading Cars Of hospitals
	for (int i = 0; i < hospitalNumber; i++) {
		int scars, ncars;
		fin >> scars >> ncars;
		hospitals[i]->LoadCars(scars, ncars);
	}

	// Patients
	int patientsNum;
	fin >> patientsNum;
	numOfRequests = patientsNum;
	int* hID_patient = new int[patientsNum];
	for (int i = 0; i < patientsNum; i++)
	{
		int reqTime, PID, HID, distance, severity = -1;
		string patientType;
		PATIENT_TYPE type;

		fin >> patientType >> reqTime >> PID >> HID >> distance;
		HID--; // 0 indexed
		hID_patient[i] = HID;
		if (strcmp(patientType.c_str(), "NP") == 0)
		{
			type = PATIENT_TYPE::NP;
		}
		else if (strcmp(patientType.c_str(), "SP") == 0)
		{
			type = PATIENT_TYPE::SP;
		}
		else // EP
		{
			type = PATIENT_TYPE::EP;
			fin >> severity;
		}
		AllPatients.enqueue(new Patient(type, PID, HID, distance, reqTime, severity));
	}

	// Cancell Requests
	int cancelNum;
	fin >> cancelNum;

	for (int i = 0; i < cancelNum; i++)
	{
		int PID, cancelTime;
		fin >> PID >> cancelTime;

		CancelRequest* req = new CancelRequest(PID, cancelTime, hID_patient[PID]);
		CancelledRequest.enqueue(req);
	}
}

//add car to out list 
void Organiser::Addout_Car(Car* car, int CurrentStep)
{
	//set arrival time takes timestep and add the time taken to reach hospital and return it 
	
	OutCars.enqueue(car, car->setArrivalTime(CurrentStep));
}

//switch car from out to back updated
void Organiser::SwitchOutToBack(int CurrentStep)
{
	Car* car = nullptr;
	int arrTime = -1;
	while (OutCars.peek(car, arrTime) && arrTime == CurrentStep)
	{
		OutCars.dequeue(car, arrTime);
		car->PickUpPatient(CurrentStep);
		BackCars.enqueue(car, car->setArrivalTime(CurrentStep));
	}
}

void Organiser::AddPatient(Patient* patient)
{
	AllPatients.enqueue(patient);
}
 
//back to free updated
void Organiser::returnCar(int CurrentStep)
{
	Car* car = nullptr;
	int arrTime = -1;
	while (BackCars.peek(car, arrTime) && arrTime == CurrentStep) {
		BackCars.dequeue(car, arrTime);
		hospitals[car->GetHospitalID()]->CarBack(car);
		FinishedRequest.enqueue(car->DropOffPatient(CurrentStep));
	}
}
void Organiser::TestGenerateOutputFile() {
	// Clear existing data
	while (!AllPatients.isEmpty()) {
		Patient* temp;
		AllPatients.dequeue(temp);
		delete temp;
	}
	while (!OutCars.isEmpty()) {
		Car* temp;
		int x;
		OutCars.dequeue(temp, x);
		delete temp;
	}
	while (!CancelledRequest.isEmpty()) {
		CancelRequest* temp;
		CancelledRequest.dequeue(temp);
		delete temp;
	}
	Patient* p1 = new Patient(PATIENT_TYPE::NP, 101, 1, 10, 5);
	Patient* p2 = new Patient(PATIENT_TYPE::SP, 102, 1, 20, 3);
	AllPatients.enqueue(p1); 
	AllPatients.enqueue(p2); // ID=102, Distance=20, PickupTime=3

	// Populate OutCars queue
	Car* car1 = new Car(CAR_TYPE::NORMAL_CAR, 2,1); // Speed=2
	Car* car2 = new Car(CAR_TYPE::NORMAL_CAR, 3,1); 

	car1->AssignPatient(p1, 1);
	car1->PickUpPatient(2); 
	car2->AssignPatient(p2, 2);
	car2->PickUpPatient(2);
	OutCars.enqueue(car1, 0);


	OutCars.enqueue(car2, 1);

	// Populate CancelledRequest queue
	CancelledRequest.enqueue(new CancelRequest(102, 10, 1)); // Patient 102 canceled

	// Call generateoutputfile()
	generateoutputfile();
}

void Organiser::generateoutputfile() {
	int epc = 0;
	int npc = 0;
	int sumwaitTime = 0;

	int spc = 0;
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

	while (AllPatients.dequeue(p1)) {
	

		Car* assignedCar = nullptr;
		int travelTime = 0.0;
		int finishTime = 0.0;
		int waitTime = 0.0;
		int i = 0;
		records arr[100];

		string status = "SERVED";
		
		switch (p1->GetType()) {
		case NP:
			npc++;
			break;
			case  SP:
				spc++;
				break;
			case EP:
				epc++;
				break;


		}

		Car* c1 = nullptr;
		int x;
		while (OutCars.dequeue(c1, x)) {
			tempCars.enqueue(c1,x); 
			if (c1 && c1->GetAssignedPatientID() == p1->GetID()) {
				assignedCar = c1;
				break;
			}
		}

		if (assignedCar != nullptr) {
			travelTime = static_cast<int>(p1->getDistance()) / assignedCar->GetSpeed();
			finishTime = p1->GetPickUpTime() + travelTime;
			waitTime = finishTime - p1->GetPickUpTime();
			sumwaitTime = sumwaitTime + waitTime;
			
		}
		else {
			status = "NO CAR"; 
		}

		while (!tempCars.isEmpty()) {
			tempCars.dequeue(c1, x);
			OutCars.enqueue(c1, x);
		}


		CancelRequest* cancelReq = nullptr;
		CancelledRequest.dequeue(cancelReq);
		if (cancelReq != nullptr && cancelReq->getPID() == p1->GetID()) {
			status = "CANCELED";
		}
		else if (cancelReq != nullptr) {
			CancelledRequest.enqueue(cancelReq); 
		}
		
		
		//myfile << finishTime << "   "
		//	<< p1->GetID() << "    "
		//	<< p1->GetPickUpTime() << "    "
		//	<< waitTime << "    "
		//	<< status << "\n";

		tempPatients.enqueue(p1);
	}

	while (!tempPatients.isEmpty()) {
		tempPatients.dequeue(p1);

		AllPatients.enqueue(p1);
	}


	myfile.close();
	cout << "File generation completed." << endl;
}

//cancel request updated
void Organiser::cancelRequest(int timestep)
{
	CancelRequest* req;
	while (CancelledRequest.peek(req) && req->getCancelTime() == timestep)
	{
		CancelledRequest.dequeue(req);
		
		Patient* p = hospitals[req->getHID()]->removepatient(req->getPID());
		if (!p)
		{
			Car* car = OutCars.cancelRequest(req->getPID());
			BackCars.enqueue(car, car->cancel(timestep));
		}
		
	}
}

void Organiser::PrintInfo()
{
	cout << "----------------------------------------" << endl;
	cout << OutCars.getCount() << " ==> Out cars: "; OutCars.printList(); cout << endl;
	cout << BackCars.getCount() << " ==> Back cars: "; BackCars.printList(); cout << endl;
	cout << "----------------------------------------" << endl;
	cout << FinishedRequest.getCount() << " finished patients: "; FinishedRequest.printList(); cout << endl;
}

void Organiser::SimulatorFunc()
{
	LoadFile();

	int count = 0;
	while (FinishedRequest.getCount() != numOfRequests && ++count)
	{
		SendPatientsToHospital(count);
		UpdateTimeStep(count);
	}
}

void Organiser::SendPatientsToHospital(int time)
{
	Patient* p = nullptr;
	AllPatients.peek(p);
	while (p && p->GetRequestTime() == time)
	{
		AllPatients.dequeue(p);
		hospitals[p->GetHID()]->addpatient(p);

		p = nullptr;
		AllPatients.peek(p);
	}
}


