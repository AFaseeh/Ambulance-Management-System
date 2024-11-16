#pragma once
#ifndef HOSPITAL_H
#define HOSPITAL_H
#include "../ADTs/LinkedQueue.h"
#include"../ADTs/priQueue.h"
#include"../ADTs/NpatientQueue.h"
#include "Organiser.h"
#include "Car.h"


class Hospital {
public:
	Hospital(Organiser* organizer);
	void addpatient(Patient* t);
	void Assignpatient(Patient* t);
	void cancelNPRequest(Patient* t);
	Hospital* getNextHospital();
	void returnCarToHospital(Patient* npPatient);
	

private:
	Organiser* organizer;
	LinkedQueue<Patient*> spQueue;        		
	priQueue<Patient*> epQueue;
	NPatientQueue npQueue;

	LinkedQueue<Car*> freeSpecialCars;
	LinkedQueue<Car*> freeNormalCars;
};
#endif