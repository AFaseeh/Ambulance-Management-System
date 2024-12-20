#pragma once
#include "../ADTs/LinkedQueue.h"
#include "../ADTs/OutCarsPriQueue.h"
#include "../headers/UI.h"
#include "CancelRequest.h"

class Hospital;


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
	void Addout_Car(Car* car,int CurrentStep);			//											**
	void SwitchOutToBack(int time);				// Puts front of "Outcars" into "Backcars"	**
	void AddPatient(Patient* patient);	// add patient to allPatients queue			**
	void returnCar(int CurrentStep);			//											**

	void cancelRequest(int timestep);	//											**

	void FinishPatient(Patient* p);
	// Collect statistics that are needed to create output file
	void PrintInfo();
	
	//Phase 1.2
	void SendPatientsToHospital(int time);

	//Phase 2
	void SendPatientToNearestHospital(Patient* p, int distance);
	void AssignAllPatientsToCars(int time);

	int FailOutCar(int currentTimeStep);
	void ReturnCarsFromCheckUp(int currentTimeStep);
	void cancelRequest(int timestep);
	void GenerateOutputFile(int timestep);

	bool SimulationFinished();
	void MainSimulation();
	void ReadInput();
};
