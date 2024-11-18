#pragma once
#include "../ADTs/LinkedQueue.h"
#include "../ADTs/OutCarsPriQueue.h"
#include "../headers/UI.h"
#include "Hospital.h"

class Organiser {
private:
	int speedSC;	//speed of special cars
	int speedNC;	// Speed of normal cars
	UI* ui;
	int hospitalNumber;
	//Hospital** hospitals;		// Array of pointers to Hospital objects
	OutCarsPriQueue* OutCars;
	priQueue<Car*>* BackCars;
	QueueADT<Patient*>* CancelledRequest;
	QueueADT<Patient*>* FinishedRequest;
	QueueADT<Patient*>* AllPatients;

public:
	Organiser();
	~Organiser();

	void UpdateTimeStep(int time);				// Gets called Every timestep
	void LoadFile();					// Loads file at program startup
	//Hospital* getHospital(int index);	
	void Addout_Car(Car* car);
	void SwitchOutToBack();
	void AddPatient(Patient* patient);		//add patient to allPatients queue

	//// check wether the patient is picked up or not and take action accordingly
	//void CancellRequest(int );

	// move patient to finished queue
	void FinishRequest(Patient* patient);

	//// assign patient to hospital
	//void assignPatientToHospital(Patient* patient);

	////move Car from outCars to backCars
	//void RemoveBackCar();

	////Collect statistics that are needed to create output file
	//void print();
};
