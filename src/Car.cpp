#include "../headers/Car.h"

int Car::staticSpeedNC = -1;
int Car::staticSpeedSC = -1;

Car::Car(CAR_TYPE type, int hospitalID, int cid) : carType(type), carStatus(CAR_STATUS::READY),
assignedPatient(nullptr), HID(hospitalID), CID(cid), arrivalTime(0), startedTime(0),busyTime(0)
{
	if (type == CAR_TYPE::NORMAL_CAR)
	{
		speed = staticSpeedNC;
	}
	else
	{
		speed = staticSpeedSC;
	}
	
}

void Car::SetStatus(CAR_STATUS status)
{
	this->carStatus = status;
}

//set patient and change start time
void Car::AssignPatient(Patient* patient,int CurrentTime)
{
	if (carStatus != CAR_STATUS::READY)
		return;
	this->carStatus = CAR_STATUS::ASSIGNED;
	this->assignedPatient = patient;
}

void Car::PickUpPatient(int currentTime)
{
	//used
	if (assignedPatient == nullptr)
		return;

	this->carStatus = CAR_STATUS::LOADED;
	busyTime += this->gettotaltime();
	assignedPatient->setPickUpTime(currentTime) ;
	startedTime = currentTime;
}

Patient* Car::DropOffPatient(int current)
{
	//usedd
	if (carStatus != CAR_STATUS::LOADED)
		return nullptr;

	busyTime += current-startedTime;	
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


int Car::setArrivalTime(int time)
{
	//used
	startedTime = time;
	arrivalTime = time+this->gettotaltime();
	return arrivalTime;
}

int Car::gettotaltime()
{
	//usedd
	return assignedPatient->getDistance()/speed;
}

int Car::cancel(int current)
{
	//used
	int time_taken = current - startedTime;
	busyTime += time_taken;
	arrivalTime = current + time_taken;
	startedTime = current;
	return (arrivalTime);
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

int Car::GetCarID() const
{
	return CID;
}

void Car::SetStaticSpeedNC(int speednc)
{
	staticSpeedNC = speednc;
}

void Car::SetStaticSpeedSC(int speedsc)
{
	staticSpeedSC = speedsc;
}

int Car::GetSpeed() const
{
	return speed;
}

std::ostream& operator<<(std::ostream& os, const Car& c)
{
	char Type = (c.carType == CAR_TYPE::NORMAL_CAR ? 'N' : 'S');
	int pid = c.GetAssignedPatientID();

	// +1 to make it 1-indexed
	std::cout << Type << c.CID << "_H" << c.HID << "_P" << pid;

	return os;
}
