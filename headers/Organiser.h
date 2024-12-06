#pragma once
#include "../ADTs/LinkedQueue.h"
#include "../ADTs/OutCarsPriQueue.h"
#include "../headers/UI.h"
#include "Hospital.h"
#include "CancelRequest.h"

class Organiser {
private:
	int** distanceMatrix;
	int hospitalNumber;
	int numOfRequests;
	UI* ui;
	Hospital** hospitals;		// Array of pointers to Hospital objects
	OutCarsPriQueue OutCars;
	priQueue<Car*> BackCars;
	LinkedQueue<CancelRequest*> CancelledRequest;
	LinkedQueue<Patient*> FinishedRequest;
	LinkedQueue<Patient*> AllPatients;

public:
	Organiser();
	~Organiser();

	void UpdateTimeStep(int time);		// Gets called Every timestep
	void LoadFile();					// Loads file at program startup
	void Addout_Car(Car* car);			//											**
	bool SwitchOutToBack();				// Puts front of "Outcars" into "Backcars"	**
	void AddPatient(Patient* patient);	// add patient to allPatients queue			**
	bool returnCar();			//											**
	void cancelRequest(int timestep);	//											**
	// Collect statistics that are needed to create output file
	void PrintInfo();

	//Phase 1.2
	void SimulatorFunc();
	void SendPatientsToHospital(int time);
};
