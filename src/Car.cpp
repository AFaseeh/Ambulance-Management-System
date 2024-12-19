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
	totalBusyTime = 0;
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
	startedTime = CurrentTime;
	if (carStatus != CAR_STATUS::READY)
		return;
	this->carStatus = CAR_STATUS::ASSIGNED;
	this->assignedPatient = patient;
}

void Car::PickUpPatient(int currentTime)
{
	if (assignedPatient == nullptr)
		return;

	this->carStatus = CAR_STATUS::LOADED;
	AddToStaticBusyTime(this->gettotaltime());	// busyTime += this->gettotaltime();
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

void Car::setArrivalTime(int StartTime, int TimeTaken)
{
	startedTime = StartTime;
	arrivalTime = StartTime + TimeTaken;
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
	AddToStaticBusyTime(time_taken);	//busyTime += time_taken;
	arrivalTime = current + time_taken;
	startedTime = current;
	return (arrivalTime);
}

void Car::SetStarted(int current)
{
	if (current >= startedTime)
	{
		startedTime = current;
	}
}

int Car::GetStarted() const
{
	return startedTime;
}


int Car::getTimeTaken(int Current) const
{
	return Current-startedTime;
}

void Car::addBusyTime(int pickupTime, int finishTime) {
	totalBusyTime += (finishTime - pickupTime);
}

int Car::getTotalBusyTime()  const {
	return totalBusyTime;
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

int Car::GetStaticCheckUpNC()
{
	return staticCheckUpNC;
}

void Car::SetStaticCheckUpSC(int time)
{
	staticCheckUpSC = time;
}

int Car::GetStaticCheckUpSC()
{
	return staticCheckUpSC;
}

void Car::SetCheckUpTimeFinish(int StartTime, int TimeTaken)
{
	endCheckUpTime = StartTime + TimeTaken;
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
