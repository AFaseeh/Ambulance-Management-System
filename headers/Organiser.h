#pragma once
#ifndef ORGANISER_H
#define ORGANISER_H
#include "../ADTs/LinkedQueue.h"
#include "../ADTs/OutCarsPriQueue.h"
#include "../headers/UI.h"

class Hospital;

class Organiser {
private:
	//speed of special cars
	int speedSC;

	// Speed of normal cars
	int speedNC;

	// UI pointer
	UI* ui;

	//total number of hospitals
	int hospitalNumber;

	//number of hospitals added
	int count;

	// Array of pointers to Hospital objects
	Hospital** hospitals;

	// Queue of cars that are currently out
	OutCarsPriQueue* OutCars;

	// Queue of cars that are currently back
	priQueue<Car*>* BackCars;

	// Queue of requests that have been cancelled
	QueueADT<Patient*>* CancelledRequest;

	// Queue of requests that have been completed
	QueueADT<Patient*>* FinishedRequest;

	// Queue of all patients 
	QueueADT<Patient*>* AllPatients;

public:
	// Constructor
	Organiser(int size);

	// Destructor
	~Organiser();

	// Update time step
	void UpdateTimeStep();

	// Load files
	void LoadFile();

	// add hospital
	void addHospital(Hospital* hospital);

	// get hospital by index
	Hospital* getHospital(int index);

	// get number of hospitals
	int getHospitalCount();

	// add car to backCars queue
	void AddBack_Car(Car* car);

	// add car to outCars queue
	void SwitchOut_Car();

	//add patient to allPatients queue
	void AddPatient(Patient* patient);

	// check wether the patient is picked up or not and take action accordingly
	void CancellRequest(int );

	// move patient to finished queue
	void FinishRequest(Patient* patient);

	// assign patient to hospital
	void assignPatientToHospital(Patient* patient);

	//move Car from outCars to backCars
	void RemoveBackCar(
		//idk
	);

	//Collect statistics that are needed to create output file
	void print();




};
#endif // ORGANISER_H
