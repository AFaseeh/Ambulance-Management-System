#pragma once
#include "Patient.h"
enum class CAR_TYPE
{
	NORMAL_CAR,
	SPECIAL_CAR
};
enum class CAR_STATUS
{
	READY,
	ASSIGNED,
	LOADED
};


class Car
{
	// Data Members
	//		Car Type: SC, NC
	//		Car Speed
	//		Car Status: Ready, Assigned, Loaded
	//		Patient Pointer
	//		Hospital ID: Constant (can't be changed after initialization)
	// Functions
	//		Assign Patient
	//		Change Status
	//		Drop Off Patient (sends patient to finish list and sets pointer to nullptr)

private:
	CAR_TYPE carType;
	CAR_STATUS carStatus;
	Patient* assignedPatient;
	//int totalTimestep;
	//int timestepLeft;
	int HID;	// 0-indexed	
	int CID;	// 0-indexed
	int speed;
	static int staticSpeedNC;
	static int staticSpeedSC;

public:
	Car(CAR_TYPE type, int hospitalID, int cid);
	void SetStatus(CAR_STATUS status);
	void AssignPatient(Patient* patient);
	void PickUpPatient();		// Car status ->Loaded
	Patient* DropOffPatient();	// Car status ->Ready
	CAR_TYPE GetType() const;
	CAR_STATUS GetStatus() const;
	int GetHospitalID() const;
	int GetAssignedPatientID() const;
	int GetCarID() const;
	friend std::ostream& operator<<(std::ostream& os, const Car& c);
	static void SetStaticSpeedNC(int staticSpeedNC);
	static void SetStaticSpeedSC(int speedsc);
	int GetSpeed() const;
};

