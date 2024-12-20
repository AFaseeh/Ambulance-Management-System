#pragma once
#include "priQueue.h"
#include "../headers/Car.h"

class CheckUpQueue : public priQueue<Car*>
{
private:
	int checkupTime;
public:
	using priQueue<Car*>::priQueue; //inheriting Base constructor
	CheckUpQueue();
	void SetCheckUpTime(int time);
	void AddCarToCheckUp(Car* toAddCar, int currentTime);
	Car* ReturnCarFromCheckUp(int currentTime);
};

