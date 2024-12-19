#include "../headers/Organiser.h"
#include "../ADTs/ArrayStack.h"

//#include "../headers/Hospital.h"
//#include "../headers/Patient.h"
//#include "../headers/Car.h"

#include "../headers/CancelRequest.h"
#include <iostream>
using namespace std;
#include <string>
#include <iomanip>

using namespace std;

Organiser::Organiser()
	: numOfRequests(-1), hospitals(nullptr), hospitalNumber(-1), distanceMatrix(nullptr)
{
	ui = new UI;
}
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
void Organiser::SimulatorFunc()
{
	int mode;
	int count = 0;

	cout << "Please select mode of operation: 0 for Interactive Mode, 1 for Silent Mode: ";
	cin >> mode;

	LoadFile();

	if (mode == 0) {
		cout << "Interactive Mode, Simulation Starts..." << endl;
		while (FinishedRequest.getCount() != numOfRequests && ++count)
		{
			cout << "Current Timestep: " << count << endl;
			SendPatientsToHospital(count);

			UpdateTimeStep(count,mode);

			cout << "Press any key to continue to the next timestep..." << endl;
			cin.ignore();
			cin.get();
		}

		GenerateOutputFile(count);
		cout << "Simulation ends, Output file created." << endl;
	}
	else if (mode == 1)
	{
		cout << "Silent Mode, Simulation Starts..." << endl;

		while (FinishedRequest.getCount() != numOfRequests && ++count)
		{
			SendPatientsToHospital(count);

			UpdateTimeStep(count,mode);
		}

		GenerateOutputFile(count);
		cout << "Simulation ends, Output file created." << endl;
	}
	else
	{
		cout << "Invalid mode selected. Please restart the program." << endl;
	}
}

void Organiser::UpdateTimeStep(int time, int mode)
{
	for (int i = 0; i < hospitalNumber; i++) {
		int random = rand() % 100 + 1;
		string message;
		bool done = true;

		if (random >= 91 && random < 95) {
			message = "Move From Back to free ";
			returnCar(time);
			if (done) {
				message = message + "\n";
			}
			else {
				message = message + "(No available car)\n";
			}
		}
		else if (random >= 80 && random < 90) {
			message = "Move from Out to Back ";
			SwitchOutToBack(time);
			if (done) {
				message = message + "\n";
			}
			else {
				message = message + "(No available car)\n";
			}
		}
		else if (random >= 70 && random < 75) {
			message = "Moving NCar from hospital[" + std::to_string(i) + "] to out list CID: ";
			Car* free = hospitals[i]->OutCar(CAR_TYPE::NORMAL_CAR);
			if (free) {
				message = message + std::to_string(free->GetCarID()) + "\n";
				OutCars.enqueue(free, 0);
			}
			else {
				message = message + "No available car\n";
			}
		}
		else if (random >= 40 && random < 45) {
			message = "Moving SCar from hospital[" + std::to_string(i) + "] to out list CID: ";
			Car* free = hospitals[i]->OutCar(CAR_TYPE::SPECIAL_CAR);
			if (free) {
				message = message + std::to_string(free->GetCarID()) + "\n";
				OutCars.enqueue(free, 0);
			}
			else {
				message = message + "No available car\n";
			}
		}
		else if (random >= 30 && random < 40) {
			message = "Moving NP from hospital[" + std::to_string(i) + "] to finish list PID: ";
			Patient* free = hospitals[i]->FinishNP();
			if (free) {
				message = message + std::to_string(free->GetID()) + "\n";
				FinishedRequest.enqueue(free);
			}
			else {
				message = message + "No available Patient\n";
			}
		}
		else if (random >= 20 && random < 25) {
			message = "Moving EP from hospital[" + std::to_string(i) + "] to finish list PID: ";
			Patient* free = hospitals[i]->FinishEP();
			if (free) {
				message = message + std::to_string(free->GetID()) + "\n";
				FinishedRequest.enqueue(free);
			}
			else {
				message = message + "No available Patient\n";
			}
		}
		else if (random >= 10 && random < 20) {
			message = "Moving SP from hospital[" + std::to_string(i) + "] to finish list PID: ";
			Patient* free = hospitals[i]->FinishSP();
			if (free) {
				message = message + std::to_string(free->GetID()) + "\n";
				FinishedRequest.enqueue(free);
			}
			else {
				message = message + "No available Patient\n";
			}
		}
		if (mode == 0) {
			ui->PrintTimeStep(this, time, hospitals[i], message);
			if (FinishedRequest.getCount() > 0) {
				message = "Finished Requests: " + std::to_string(FinishedRequest.getCount()) + "\n";
				ui->PrintMessage(message);
			}
		}
		if (FinishedRequest.getCount() == numOfRequests) {
			ui->PrintMessage("Finished Simulation");
			return;
		}
	}


}

void Organiser::LoadFile()
{
	string fname = ui->Loadfile();

	std::cout << fname << endl;

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
    int speedSC, speedNC, outfailprobability;
    fin >> speedSC >> speedNC;
    fin >> outfailprobability;
    Car::SetStaticSpeedNC(speedNC);
    Car::SetStaticSpeedSC(speedSC);
    Car::SetStaticOutFailProbability(outfailprobability);


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
		
		switch (car->GetStatus())
		{
		case CAR_STATUS::OUT_FAILED:
			hospitals[car->GetHospitalID()]->FailedCarBack(car, CurrentStep);
			break;	
		default:
			hospitals[car->GetHospitalID()]->CarBack(car);
			FinishPatient(car->DropOffPatient(CurrentStep));
			break;
		}
	}
}








void Organiser::FinishPatient(Patient* p)
{
	if (p)
	{
		AllPatients.enqueue(p);
	}
}

void Organiser::PrintInfo()
{
	std::cout << "----------------------------------------" << endl;
	std::cout << OutCars.getCount() << " ==> Out cars: "; OutCars.printList(); cout << endl;
	std::cout << BackCars.getCount() << " ==> Back cars: "; BackCars.printList(); cout << endl;
	std::cout << "----------------------------------------" << endl;
	std::cout << FinishedRequest.getCount() << " finished patients: "; FinishedRequest.printList(); cout << endl;
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

int Organiser::FailOutCar(int currentTimeStep)
{
	Car* c = OutCars.GetRandomOutCarToFail();

	if (c == nullptr)
	{
		return -2;
	}

	Car* x = OutCars.cancelRequest(c->GetAssignedPatientID());

	if (c != x)
	{
		return -1;
	}

	c->SetStatus(CAR_STATUS::OUT_FAILED);
	c->setArrivalTime(currentTimeStep, c->getTimeTaken(currentTimeStep));
	BackCars.enqueue(c, -c->getArrivalTime());
	return 0;
}

void Organiser::ReturnCarsFromCheckUp(int time)
{
	for (int i = 0; i < hospitalNumber; i++)
	{
		hospitals[i]->CompleteCarsCheckUp(time);
	}
}



void Organiser::GenerateOutputFile(int timestep) {

	std::ofstream myfile("output.txt");
	if (!myfile.is_open()) {
		std::cout << "Unable to open file for output!" << std::endl;
		return;
	}

	myfile << "FT   PID    QT     WT    STATUS\n";
	int npc = 0, spc = 0, epc = 0;
	int ncc = 0, scc = 0;

	int totalWaitTime = 0, totalBusyTime = 0;
	int countcars = 0;
	int totalbusytime = 0;
	std::string status;
	while (!FinishedRequest.isEmpty()) {

		Patient* p1;
		FinishedRequest.dequeue(p1);
		int waitTime = p1->GetPickUpTime() - p1->GetRequestTime();
		if (p1->GetType() == PATIENT_TYPE::NP) npc++;
		if (p1->GetType() == PATIENT_TYPE::SP) spc++;

		if (p1->GetType() == PATIENT_TYPE::EP) epc++;
		totalWaitTime += waitTime;
		if (p1->GetPickUpTime() != -1) {
			status = "PICKED";
			myfile << std::setw(8) << p1->GetPickUpTime()
				<< std::setw(8) << p1->GetID()
				<< std::setw(8) << p1->GetRequestTime()
				<< std::setw(8) << waitTime
				<< std::setw(12) << status << "\n";
		}
		else {
			status = "NO CAR";
			myfile << std::left << std::setw(8) << "N/A"
				<< std::setw(8) << p1->GetID()
				<< std::setw(8) << p1->GetRequestTime()
				<< std::setw(8) << "N/A"
				<< std::setw(12) << status << "\n";
		}

	}
	Car* c1 = nullptr;
	int t;
	LinkedQueue<Car*> car1;
	LinkedQueue<Car*> car2;

	for (int i = 0; i < hospitalNumber; i++) {
		car1 = hospitals[i]->GetFreeNormalCars();
		car2 = hospitals[i]->GetFreeSpecialCars();
		while (car1.dequeue(c1)) {
			countcars++;
			if (c1->GetType() == CAR_TYPE::NORMAL_CAR) {
				ncc++;
			}
			else {
				scc++;

			}
			totalbusytime += c1->getTotalBusyTime();


		}
		while (car2.dequeue(c1)) {
			countcars++;
			if (c1->GetType() == CAR_TYPE::NORMAL_CAR) {
				ncc++;
			}
			else {
				scc++;

			}
			totalbusytime += c1->getTotalBusyTime();


		}


	}
	while (OutCars.dequeue(c1, t)) {
		countcars++;

		if (c1->GetType() == CAR_TYPE::NORMAL_CAR) {
			ncc++;
		}
		else {
			scc++;

		}
		totalbusytime += c1->getTotalBusyTime();

	}
	while (BackCars.dequeue(c1, t)) {
		countcars++;
		if (c1->GetType() == CAR_TYPE::NORMAL_CAR) {
			ncc++;
		}
		else {
			scc++;

		}

		totalbusytime += c1->getTotalBusyTime();

	}

	int totalPatients = npc + spc + epc;
	myfile << "patients: " << totalPatients << "   "
		<< "[NP: " << npc << ", SP: " << spc << ", EP: " << epc << "]\n";
	myfile << "hospitals: " << hospitalNumber - 1 << '\n';
	myfile << "Cars: " << countcars << "   "
		<< "[Scar: " << scc << ", NCar: " << ncc  << "]\n";
	myfile << "Avg wait Time: " << (totalPatients > 0 ? totalWaitTime / totalPatients : 0) << '\n';
	myfile << "Avg busy time: " << (countcars > 0 ? totalbusytime / countcars : 0) << '\n';
	myfile << "Avg utilization time: " << (totalbusytime > 0 ? (totalbusytime / timestep) * 100 : 0) << "%" << '\n';

	myfile.close();
	std::cout << "File generation completed." << std::endl;

}
