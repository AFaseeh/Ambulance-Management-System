#pragma once
#include "../ADTs/LinkedQueue.h"
#include"../ADTs/priQueue.h"
#include"../ADTs/NpatientQueue.h"
#include "Car.h"

class Organiser;

class Hospital {
private:
	Organiser* organiser;
	LinkedQueue<Patient*> spQueue;
	priQueue<Patient*> epQueue;
	NPatientQueue npQueue;
	LinkedQueue<Car*> freeSpecialCars;
	LinkedQueue<Car*> freeNormalCars;
	int hospitalID; // 0-indexed

public:
	Hospital(Organiser* organiser, int id);
	~Hospital();
	void addpatient(Patient* t);
	void Assignpatient(Patient* t);
	void LoadCars(int sCars, int nCars);
	friend ostream& operator<<(ostream& os, const Hospital& h);
	// Phase 1.2
	void CarBack(Car* car);
	Car* OutCar(CAR_TYPE type);
	Patient* FinishSP();
	Patient* FinishEP();
	Patient* FinishNP();

};