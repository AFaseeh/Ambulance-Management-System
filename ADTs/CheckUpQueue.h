#pragma once
#include "LinkedQueue.h"
#include "../headers/Car.h"

class CheckUpQueue : public LinkedQueue<Car*>
{
private:
	int checkupTime;
public:
	using LinkedQueue<Car*>::LinkedQueue; //inheriting Base constructor
	CheckUpQueue();
	void SetCheckUpTime(int time);
	void AddCarToCheckUp(Car* toAddCar, int currentTime);
	Car* ReturnCarFromCheckUp(int currentTime);

};

