#pragma once
#include <iostream>

enum PATIENT_TYPE
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
	int HID;
	int DistanceToHospital;
	PATIENT_TYPE Type;
	int Severity;
public:
	Patient(PATIENT_TYPE type, int PID, int HID, int distance, int requestTime,int severity = 0);
	int GetSeverity() const;
	void SetSeverity(int severity);
	int GetID() const;
	PATIENT_TYPE GetType() const;
	void setPickUpTime(int time);
	int GetPickUpTime() const;
	int GetHID() const;
	int GetRequestTime() const;
	void SetHID(int ID);
	void SetDistance(int Distance);
	int getDistance() const;
	friend std::ostream& operator<<(std::ostream& os, const Patient& p);
	//idk
	//void Print();
};

