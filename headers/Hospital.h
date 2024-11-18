#pragma once
#include "../ADTs/LinkedQueue.h"
#include"../ADTs/priQueue.h"
#include"../ADTs/NpatientQueue.h"
#include "Car.h"

class Organiser;

class Hospital {
public:
	Hospital(Organiser* organiser);
	void addpatient(Patient* t);
	void Assignpatient(Patient* t);
	void cancelNPRequest(Patient* t);
	//Hospital* getNextHospital();
	//void returnCarToHospital(Patient* npPatient);

private:
	Organiser* organiser;
	LinkedQueue<Patient*> spQueue;
	priQueue<Patient*> epQueue;
	NPatientQueue npQueue;

	LinkedQueue<Car*> freeSpecialCars;
	LinkedQueue<Car*> freeNormalCars;
};