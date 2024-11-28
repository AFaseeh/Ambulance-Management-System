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
}

void Organiser::UpdateTimeStep(int time)
{
	for (int i = 0; i < hospitalNumber; i++) {
		int random = rand() % 100+1;
        string message;
        if (random >= 91 && random<95) {
            //move car from back to free list of its hospital
            message = "Move From Back to free ";
            Car* car = nullptr;
            int priority;
			BackCars.dequeue(car,priority);
            if (car)
            {
                hospitals[car->GetHospitalID()]->CarBack(car);
                message = message + "\n";
            }
            else
                message = message + "(No available car)\n";
        }
        else if (random >= 80 && random<90) {
        //move car from out to back list
            message = "Move from Out to Back ";
            int trashOutPut = -1;
            Car* c = nullptr;
            OutCars.dequeue(c, trashOutPut);
            if (c)
            {
                BackCars.enqueue(c, trashOutPut);
                message = message + "\n";
            }
            else
                message = message + "(No available car)\n";
        }
        else if (random >= 70 && random<75) {
            // take a patient from all patients and assign to car 
            // need a function to send out a specific car in hospital or create a dummy normal patient ?

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
        else if (random >= 40&& random <45) {
			//same as above but for special car
            message =  "Moving SCar from hospital[" + std::to_string(i) +"] to out list CID: ";
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
        else if (random >= 30 && random<40) {
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
        else if (random >= 20 && random <25)
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
        else if (random >= 10 && random<20) {
			//move SP patient to finished
            message =  "Moving SP from hospital[" + std::to_string(i) + "] to finish list PID: ";
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
    hospitals = new Hospital*[hospitalNumber];
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
