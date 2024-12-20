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
	LOADED,
	IN_CHECKUP,
	OUT_FAILED,
	PATIENT_CANCELLED
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
	int startedTime;
	int arrivalTime; //time at which car arrives at hospital
	int HID;	// 0-indexed	
	int CID;	// 0-indexed
	int speed;
	int endCheckUpTime;
	int carCheckupTime;

	static int staticBusyTime;
	static int staticSpeedNC;
	static int staticSpeedSC;
	static int staticOutFailProbability;
	static int staticCheckUpNC;
	static int staticCheckUpSC;

public:
	Car(CAR_TYPE type, int hospitalID, int cid);
	void SetStatus(CAR_STATUS status);
	void AssignPatient(Patient* patient,int CurrentTime);
	void PickUpPatient(int currentTime);		// Car status ->Loaded
	Patient* DropOffPatient(int current);	// Car status ->Ready
	CAR_TYPE GetType() const;
	CAR_STATUS GetStatus() const;

	int setArrivalTime(int time);
	int getArrivalTime() const;

	int gettotaltime() const;

	int GetHospitalID() const;
	int GetAssignedPatientID() const;
	int GetCarID() const;

	friend std::ostream& operator<<(std::ostream& os, const Car& c);

	// Static functions
	static void SetStaticSpeedNC(int staticSpeedNC);
	static void SetStaticSpeedSC(int speedsc);
	static void SetStaticOutFailProbability(int prob);
	static int GetStaticOutFailProbability();
	static void AddToStaticBusyTime(int time);
	static int GetStaticBusyTime();
	static void SetStaticCheckUpNC(int time);
	static void SetStaticCheckUpSC(int time);

	// Car Check up
	void SetCheckUpTimeFinish(int StartTime);
	int GetCheckUpTimeFinish() const;
	Patient* ReturnPatientToHospital();
	int GetCarCheckUpTime() const;
	void setOutCarFailureArrivalTime(int StartTime);
		 
	Patient* CancelPatient(int time);
};

