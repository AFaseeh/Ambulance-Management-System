#include "../headers/Organiser.h"
//#include "../headers/Hospital.h"
//#include "../headers/Patient.h"
//#include "../headers/Car.h"
#include <iostream>
using namespace std;

Organiser::Organiser() {
    LoadFile();
}

Organiser::~Organiser() {
    for (int i = 0; i < hospitalNumber; ++i) {
        delete hospitals[i];
    }
    delete[] hospitals;
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
    //load data (speedNC,speddSC, hospitals, allpatient)
}

//FASEH

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


    OutCars->enqueue(car, priority);
}

//switch car from back to out
void Organiser::SwitchOutToBack()
{
	Car* car;
    int time;
    OutCars->dequeue(car, time);
	BackCars->enqueue(car, time);
}

void Organiser::AddPatient(Patient* patient)
{
    AllPatients->enqueue(patient);
}

void Organiser::FinishRequest(Patient* patient)
{
    //check if patient can be finished or not
    //if (OutCars->dequeue(patient->GetID(),)) {
    //	FinishedRequest->enqueue(patient);
    //}
}
