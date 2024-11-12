#pragma once
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
	int NearestHospitalID;
	int DistanceToHospital;
	PATIENT_TYPE Type;
	int Severity;
public:
	Patient(PATIENT_TYPE type, int PID, int HID, int distance, int requestTime,int severity = 0);
	int GetSeverity();
	int GetID();
	PATIENT_TYPE GetType();
	int GetPickUpTime();
	void SetHID(int ID);
	void SetDistance(int Distance);
	//idk
	//void Print();
};

