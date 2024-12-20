#include "../headers/Car.h"

int Car::staticSpeedNC = -1;
int Car::staticSpeedSC = -1;
int Car::staticOutFailProbability = -1;
int Car::staticBusyTime = 0;
int Car::staticCheckUpNC = 0;
int Car::staticCheckUpSC = 0;

Car::Car(CAR_TYPE type, int hospitalID, int cid) : carType(type), carStatus(CAR_STATUS::READY),
assignedPatient(nullptr), HID(hospitalID), CID(cid), arrivalTime(0), startedTime(0), endCheckUpTime(0)
{
	if (type == CAR_TYPE::NORMAL_CAR)
	{
		speed = staticSpeedNC;
		carCheckupTime = staticCheckUpNC;
	}
	else
	{
		speed = staticSpeedSC;
		carCheckupTime = staticCheckUpSC;
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
	
	startedTime = CurrentTime;
	this->carStatus = CAR_STATUS::ASSIGNED;
	this->assignedPatient = patient;
}

void Car::PickUpPatient(int currentTime)
{
	if (assignedPatient == nullptr)
		return;

	this->carStatus = CAR_STATUS::LOADED;
	AddToStaticBusyTime(currentTime - startedTime);	// busyTime += this->gettotaltime();
	assignedPatient->setPickUpTime(currentTime) ;
	startedTime = currentTime;
}
Patient* Car::DropOffPatient(int current)
{
	if (carStatus != CAR_STATUS::LOADED)
		return nullptr;

	AddToStaticBusyTime(current-startedTime); //busyTime += current-startedTime;
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

int Car::getArrivalTime() const
{
	return arrivalTime;
}


int Car::setArrivalTime(int time)
{
	//used
	startedTime = time;
	arrivalTime = time+this->gettotaltime();
	return arrivalTime;
}

void Car::setOutCarFailureArrivalTime(int current)
{
	int time_taken = current - startedTime;
	startedTime = current;
	arrivalTime = current + time_taken;
}

int Car::gettotaltime() const
{
	//usedd
	return std::ceil((float)assignedPatient->getDistance()/speed);
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

void Car::SetStaticOutFailProbability(int prob)
{
	if (prob >= 0 && prob <= 100)
	{
		staticOutFailProbability = prob;
	}
}

int Car::GetStaticOutFailProbability()
{
	return staticOutFailProbability;
}

void Car::AddToStaticBusyTime(int time)
{
	staticBusyTime += time;
}

int Car::GetStaticBusyTime()
{
	return staticBusyTime;
}

void Car::SetStaticCheckUpNC(int time)
{
	staticCheckUpNC = time;
}

void Car::SetStaticCheckUpSC(int time)
{
	staticCheckUpSC = time;
}

void Car::SetCheckUpTimeFinish(int StartTime)
{
	endCheckUpTime = StartTime + carCheckupTime;
}

int Car::GetCheckUpTimeFinish() const
{
	return endCheckUpTime;
}

Patient* Car::ReturnPatientToHospital()
{
	Patient* p = assignedPatient;
	assignedPatient = nullptr;
	return p;
}

int Car::GetCarCheckUpTime() const
{
	return carCheckupTime;
}

Patient* Car::CancelPatient(int current)
{
	Patient* p = assignedPatient;
	assignedPatient = nullptr;
	carStatus = CAR_STATUS::PATIENT_CANCELLED;
	int time_taken = current - startedTime;
	startedTime = current;
	arrivalTime = startedTime + time_taken;

	return p;
}

std::ostream& operator<<(std::ostream& os, const Car& c)
{
	char Type = (c.carType == CAR_TYPE::NORMAL_CAR ? 'N' : 'S');
	
	int pid = -1;
	if (c.assignedPatient != nullptr)
	{
		pid = c.GetAssignedPatientID();
	}

	// +1 to make it 1-indexed
	std::cout << Type << c.CID << "_H" << c.HID << "_P" << pid;

	return os;
}
