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
	Patient* removepatient(int pid);
	void Assignpatient();
	void LoadCars(int sCars, int nCars);
	// Getter for freeSpecialCars
	LinkedQueue<Car*>& GetFreeSpecialCars();

	// Getter for freeNormalCars
	LinkedQueue<Car*>& GetFreeNormalCars();
	
	friend ostream& operator<<(ostream& os, const Hospital& h);
	// Phase 1.2
	void CarBack(Car* car);
	Car* OutCar(CAR_TYPE type);
	Patient* FinishSP();
	Patient* FinishEP();
	Patient* FinishNP();

	//assigning paitents
	void AssignNP();
	void AssignSP();
	void AssignEP();

};