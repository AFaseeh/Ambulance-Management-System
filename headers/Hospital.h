#pragma once
#include "../ADTs/LinkedQueue.h"
#include"../ADTs/priQueue.h"
#include"../ADTs/NpatientQueue.h"
#include"../ADTs/CheckUpQueue.h"
#include"../ADTs/EPatientQueue.h"
#include"../ADTs/SPatientQueue.h"
#include "Car.h"

class Organiser;

class Hospital {
private:
	Organiser* organiser;
	SPatientQueue spQueue;
	EPatientQueue epQueue;
	NPatientQueue npQueue;
	LinkedQueue<Car*> freeSpecialCars;
	LinkedQueue<Car*> freeNormalCars;
	CheckUpQueue CheckUpList;
	int hospitalID; // 0-indexed
	int checkUpTimeSC;
	int checkUpTimeNC;

public:
	Hospital(Organiser* organiser, int id);
	~Hospital();
	void addpatient(Patient* t);
	Patient* removepatient(int pid);
	void LoadCars(int sCars, int nCars);
	
	friend ostream& operator<<(ostream& os, const Hospital& h);
	// Phase 1.2
	void CarBack(Car* car);
	void FailedCarBack(Car* c, int timeStep);
	void CompleteCarsCheckUp(int timestep);
	void ReassignPatientToHospital(Patient* p);
	Car* OutCar(CAR_TYPE type);

	//assigning paitents
	void AssignHospitalPatientsToCars(int time);
	Car* AssignNP();
	Car* AssignSP();
	Car* AssignEP();
};
