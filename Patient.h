#include "Car.h"
#pragma once
enum PatientType
{
	NP,SP,EP
};
class Patient
{
	// Data Members
	//		Request Time
	//		Pickup Time
	//		Patient's nearest Hospital: ID of the hospital
	//		Distance: the distance between nearest hospital and the patient
	//		Patient Type: Special Patient(SP), Emergency Patient(EP), Normal Patient(NP)
private:
	int PatientID;
	int RequestTime;
	int PickUpTime;
	int NearestHospitalID;
	int DistanceToHospital;
	PatientType Type;
	int Severity;
	Car* AssignedCar = nullptr;
public:
	Patient(PatientType type, int PID, int HID, int distance, int Severity);
	int GetSeverity();

	PatientType GetType();

	int GetPickUpTime();

	bool IsAssigned();

	void SetHID(int ID);

	void SetDistance(int Distance);

	void AssignCar(Car* assigned);

	//idk
	void Print();
};

