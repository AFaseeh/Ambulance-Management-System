#include "../headers/Patient.h"

Patient::Patient(PATIENT_TYPE type, int PID, int HID, int distance, int reqTime, int severity)
	:PatientID(PID), NearestHospitalID(HID), Type(type), RequestTime(reqTime),
	PickUpTime(-1), Severity(severity), DistanceToHospital(distance)
{
}

int Patient::GetSeverity()
{
	return Severity;
}

int Patient::GetID()
{
	return PatientID;
}

PATIENT_TYPE Patient::GetType()
{
	return Type;
}

int Patient::GetPickUpTime()
{
	return PickUpTime;
}

void Patient::SetHID(int ID)
{
	ID = NearestHospitalID;
}

void Patient::SetDistance(int Distance)
{
	Distance = DistanceToHospital;
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	// TODO: insert return statement here
	std::cout << "PatientID: " << p.PatientID << std::endl;


	return os;
}
