#include "../headers/Organiser.h"
//#include "../headers/Hospital.h"
//#include "../headers/Patient.h"
//#include "../headers/Car.h"
#include "../headers/CancelRequest.h"
#include <iostream>
using namespace std;

Organiser::Organiser()
    : speedNC(-1), speedSC(-1), numOfRequests(-1), hospitals(nullptr), hospitalNumber(-1), distanceMatrix(nullptr)
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
}

void Organiser::UpdateTimeStep(int time)
{
	for (int i = 0; i < hospitalNumber; i++) {
        cout << "\033[2J\033[H"; // Clears window
        cout << "Current Timestep: " << time << endl;

        cout << *hospitals[i];
		int random = rand() % 100+1;
        if (random >= 91 && random<95) {
            //move car from back to free list of its hospital
            cout << "Move From Back to free" << endl;
            Car* car = nullptr;
            int priority;
			BackCars.dequeue(car,priority);
            if (car)
                hospitals[car->GetHospitalID()]->CarBack(car);
        }
        else if (random >= 80 && random<90) {
        //move car from out to back list
            int trashOutPut = -1;
            Car* c = nullptr;
            OutCars.dequeue(c, trashOutPut);
            if (c)
                BackCars.enqueue(c, trashOutPut);
        }
        else if (random >= 70 && random<75) {
            // take a patient from all patients and assign to car 
            //Patient* patient;
            // need a function to send out a specific car in hospital or create a dummy normal patient ?
			/*AllPatients->dequeue(patient);
            hospitals[i]->Assignpatient(patient);*/

            cout << "Moving NCar from hospital[" << i << "] to Free out list CID: ";
            Car* free = hospitals[i]->OutCar(CAR_TYPE::NORMAL_CAR);
            if (free)
            {
                cout << *free << endl;
                OutCars.enqueue(free, 0);
            }
            else
            {
                cout << endl;
            }
        }
        else if (random >= 40&& random <45) {
			//same as above but for special car
            cout << "Moving SCar from hospital[" << i << "] to Free out list CID: ";
            Car* free = hospitals[i]->OutCar(CAR_TYPE::SPECIAL_CAR);
            if (free)
            {
                cout << *free << endl;
                OutCars.enqueue(free, 0);
            }
            else
            {
                cout << endl;
            }
        }
        else if (random >= 30 && random<40) {
			//move NP patient to finished
            cout << "Moving NP from hospital[" << i << "] to finish list PID: ";
            Patient* free = hospitals[i]->FinishNP();
            if (free)
            {
                cout << *free << endl;
                FinishedRequest.enqueue(free);
            }
            else
            {
                cout << endl;
            }
        }
        else if (random >= 20 && random <25)
        {
			//move EP patient to finished
            cout << "Moving EP from hospital[" << i << "] to finish list PID: ";
            Patient* free = hospitals[i]->FinishEP();
            if (free)
            {
                cout << *free << endl;
                FinishedRequest.enqueue(free);
            }
            else
            {
                cout << endl;
            }
        }
        else if (random >= 10 && random<20) {
			//move SP patient to finished
            cout << "Moving SP from hospital[" << i << "] to finish list PID: ";
            Patient* free = hospitals[i]->FinishSP();
            if (free)
            {
                cout << *free << endl;
                FinishedRequest.enqueue(free);
            }
            else
            {
                cout << endl;
            }
        }

        cout << *hospitals[i];

        cout << "----------------------------------------" << endl;
        cout << OutCars.getCount() << " ==> Out cars: "; OutCars.printList(); cout << endl;
        cout << BackCars.getCount() << " ==> Back cars: "; BackCars.printList(); cout << endl;
        cout << "----------------------------------------" << endl;
        cout << FinishedRequest.getCount() << " finished patients: "; FinishedRequest.printList(); cout << endl;
        cout << AllPatients.getCount() << " All patients: "; AllPatients.printList(); cout << endl;

        if (FinishedRequest.getCount() == numOfRequests)
        {
            cout << "Finished Simulation" << endl;
            return;
        }

        cout << "enter any value to continue" << endl;
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
        hospitals[i] = new Hospital(this, i);
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
*/

void Organiser::Addout_Car(Car* car)
{
    // Priority Should be calculated
    // Distance to hospital / speed of car
    int priority = -1;
    OutCars.enqueue(car, priority);
}

//switch car from back to out
void Organiser::SwitchOutToBack()
{
	Car* car;
    int time;
    OutCars.dequeue(car, time);

    // Calculate return to hospital time and push it with this priority
    // time = ...
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

void Organiser::SimulatorFunc()
{
    LoadFile();

    for (int i = 0; i < numOfRequests; i++)
    {
        Patient* p = nullptr;
        AllPatients.dequeue(p);
        hospitals[p->GetHID()]->addpatient(p);
    }

    int count = 0;
    while (FinishedRequest.getCount() != numOfRequests && ++count)
    {
        UpdateTimeStep(count);
    }
}
