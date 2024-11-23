#include "../headers/Car.h"

Car::Car(CAR_TYPE type, int hospitalID, int cid) : carType(type), carStatus(CAR_STATUS::READY),
														assignedPatient(nullptr), HID(hospitalID), CID(cid)
{}

void Car::SetStatus(CAR_STATUS status)
{
	this->carStatus = status;
}

void Car::AssignPatient(Patient* patient)
{
	if (carStatus != CAR_STATUS::READY)
		return;

	this->carStatus = CAR_STATUS::ASSIGNED;
	this->assignedPatient = patient;
}

void Car::PickUpPatient()
{
	if (assignedPatient == nullptr)
		return;

	this->carStatus = CAR_STATUS::LOADED;
	/*timestepLeft = totalTimestep;*/
}

Patient* Car::DropOffPatient()
{
	if (carStatus != CAR_STATUS::LOADED)
		return nullptr;

	Patient* patient = this->assignedPatient;
	this->assignedPatient = nullptr;
	this->carStatus = CAR_STATUS::READY;

	return patient;
}

CAR_TYPE Car::GetType() const
{
	return carType;
}

CAR_STATUS Car::GetStatus() const
{
	return carStatus;
}

int Car::GetHospitalID() const
{
	return HID;
}

int Car::GetAssignedPatientID() const
{
	if (carStatus != CAR_STATUS::READY && assignedPatient)
	{
		return (assignedPatient->GetID());
	}
	return -1;
}

int Car::GetTimeStepLeft() const
{
	if (carStatus != CAR_STATUS::READY)
	{
		//return timestepLeft;
	}
	return -1;
}

std::ostream& operator<<(std::ostream& os, const Car& c)
{
	char Type = (c.carType == CAR_TYPE::NORMAL_CAR ? 'N' : 'S');
	int pid = c.GetAssignedPatientID();

	// +1 to make it 1-indexed
	std::cout << Type << c.CID + 1 << "_H" << c.HID + 1 << "_P" << pid;

	return os;
}
