#include "../headers/Patient.h"

Patient::Patient(PATIENT_TYPE type, int PID, int HID, int distance, int reqTime, int severity)
	:PatientID(PID), HID(HID), Type(type), RequestTime(reqTime),
	PickUpTime(-1), Severity(severity), DistanceToHospital(distance)
{
}

int Patient::GetSeverity() const
{
	return Severity;
}

int Patient::GetID() const
{
	return PatientID;
}

PATIENT_TYPE Patient::GetType() const
{
	return Type;
}

int Patient::GetPickUpTime() const
{
	return PickUpTime;
}

int Patient::GetHID() const
{
	return HID;
}

int Patient::GetRequestTime() const
{
	return RequestTime;
}

void Patient::SetHID(int ID)
{
	HID = ID;
}

void Patient::SetDistance(int Distance)
{
	DistanceToHospital = Distance;
}

int Patient::getDistance() const
{
	return DistanceToHospital;
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	// TODO: insert return statement here
	std::cout << p.PatientID;
	return os;
}
