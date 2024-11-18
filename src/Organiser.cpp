#include "../headers/Organiser.h"
//#include "../headers/Hospital.h"
//#include "../headers/Patient.h"
//#include "../headers/Car.h"
#include "../headers/CancelRequest.h"
#include <iostream>
using namespace std;

Organiser::Organiser() {
    LoadFile();

    cout << "Hospitals: " << hospitalNumber << endl;
    cout << "Patients: " << endl;
    for (int i = 0; i < pendingRequests; i++)
    {
        Patient* p;
        AllPatients.dequeue(p);
        cout << *p << endl;
    }
}

Organiser::~Organiser() {
    for (int i = 0; i < hospitalNumber; ++i) {
        delete hospitals[i];
        delete[] distanceMatrix[i];
    }
    delete[] hospitals;
    delete[] distanceMatrix;
}

void Organiser::UpdateTimeStep(int time)
{
	for (int i = 0; i < hospitalNumber; i++) {
		int random = rand() % 100+1;
        if (random >= 91 && random<95) {
            //move car from back to free list of its hospital
            //Car* car;
            //int priority;
			//BackCars->dequeue(car,priority);
			//hospitals[i]->returnCarToHospital();
            
        }
        else if (random >= 80 && random<90) {
        //move car from out to back list
			
            SwitchOutToBack();
            
        }
        else if (random >= 70 && random<75) {
            // take a patient from all patients and assign to car 
            //Patient* patient;
            // need a function to send out a specific car in hospital or create a dummy normal patient ?
			/*AllPatients->dequeue(patient);
            hospitals[i]->Assignpatient(patient);*/
        }
        else if (random >= 40&& random <45) {
			//same as above but for special car
        }
        else if (random >= 30 && random<40) {
			//move NP patient to finished
        }
        else if (random >= 20 && random <25)
        {
			//move EP patient to finished
        }
        else if (random >= 10 && random<20) {
			//move SP patient to finished
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
    hospitals = new Hospital*[hospitalNumber];
    for (int i = 0; i < hospitalNumber; i++) {
        hospitals[i] = new Hospital(this, i+1);
    }

    // Loading Speed of Cars
    fin >> speedSC >> speedNC;

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
    pendingRequests = patientsNum;
    int* hID_patient = new int[patientsNum];
    for (int i = 0; i < patientsNum; i++)
    {
        int reqTime, PID, HID, distance, severity = -1;
        string patientType;
        PATIENT_TYPE type;
      
        fin >> patientType >> reqTime >> PID >> HID >> distance;
        hID_patient[i] = HID;
        if (strcmp(patientType.c_str(), "NP") == 0)
        {
            type = PATIENT_TYPE::NP;
        }
        else if (strcmp(patientType.c_str(), "SP") == 0)
        {
            type = PATIENT_TYPE::SP;
        }
        else if (strcmp(patientType.c_str(), "EP") == 0)
        {
            type = PATIENT_TYPE::EP;
            fin >> severity;
        }
        AllPatients.enqueue(new Patient(PATIENT_TYPE::NP, PID, HID, distance, reqTime, severity));
    }

    // Cancell Requests
    int cancelNum;
    fin >> cancelNum;

    for (int i = 0; i < cancelNum; i++)
    {
        int PID, cancelTime;
        fin >> PID >> cancelTime;

        CancelRequest* req = new CancelRequest(PID, cancelTime, hID_patient[PID]);
    }
}

/*
Hospital* Organiser::getHospital(int index) {
    if (index >= 0 && index < hospitalNumber) {
        //return hospitals[index];
    }
    return nullptr;
}
*/

void Organiser::Addout_Car(Car* car)
{

    //Distance to hospital / speed of car
    int priority = 5;


    OutCars.enqueue(car, priority);
}

//switch car from back to out
void Organiser::SwitchOutToBack()
{
	Car* car;
    int time;
    OutCars.dequeue(car, time);
	BackCars.enqueue(car, time);
}

void Organiser::AddPatient(Patient* patient)
{
    AllPatients.enqueue(patient);
}

void Organiser::FinishRequest(Patient* patient)
{
    //check if patient can be finished or not
    //if (OutCars->dequeue(patient->GetID(),)) {
    //	FinishedRequest->enqueue(patient);
    //}
}
