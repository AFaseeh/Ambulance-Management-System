#include "Patient.h"

Patient::Patient(PatientType type, int PID, int HID, int distance, int Severity = 0)
{
	this->Type = type;
	PatientID = PID;
	NearestHospitalID = HID;
	DistanceToHospital = distance;
}

int Patient::GetSeverity()
{
	return Severity;
}

PatientType Patient::GetType()
{
	return Type;
}

int Patient::GetPickUpTime()
{
	return PickUpTime;
}

bool Patient::IsAssigned()
{
	return AssignedCar != nullptr;
}

void Patient::SetHID(int ID)
{
	ID = NearestHospitalID;
}

void Patient::SetDistance(int Distance)
{
	Distance = DistanceToHospital;
}

void Patient::AssignCar(Car* assigned)
{
	AssignedCar = assigned;
}