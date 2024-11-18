#include "../headers/Organiser.h"
#include "../headers/Hospital.h"
#include "../headers/Patient.h"
#include "../headers/Car.h"
#include <iostream>
using namespace std;

class Hospital;

Organiser::Organiser(int size) {
    hospitalNumber = size;
    count = 0;
    hospitals = new Hospital * [hospitalNumber];
}

Organiser::~Organiser() {
    for (int i = 0; i < count; ++i) {
        delete hospitals[i];
    }
    delete[] hospitals;
}

void Organiser::UpdateTimeStep()
{

}

void Organiser::LoadFile()
{
    //load data (speedNC,speddSC, hospitals, allpatient)
}

//FASEH
void Organiser::addHospital(Hospital* hospital) {
    if (count < hospitalNumber) {
        hospitals[count] = hospital;
        ++count;
    }
    else {
        std::cout << "Organiser is full, cannot add more hospitals." << std::endl;
    }
}

Hospital* Organiser::getHospital(int index) {
    if (index >= 0 && index < count) {
        return hospitals[index];
    }
    return nullptr;
}

int Organiser::getHospitalCount() {
    return count;
}

void Organiser::AddBack_Car(Car* car)
{

    //Distance to hospital / speed of car
    int priority;


    BackCars->enqueue(car, priority);
}

//switch car from back to out
void Organiser::SwitchOut_Car()
{
	Car* car;
    int time;
	BackCars->dequeue(car, time);
    OutCars->enqueue(car, time);
}

void Organiser::AddPatient(Patient* patient)
{
    AllPatients->enqueue(patient);
}

void Organiser::CancellRequest(int PID)
{
  

}

void Organiser::FinishRequest(Patient* patient)
{
    //check if patient can be finished or not
    //if (OutCars->dequeue(patient->GetID(),)) {
    //	FinishedRequest->enqueue(patient);
    //}
}

void Organiser::assignPatientToHospital(Patient* patient)
{
 
}
