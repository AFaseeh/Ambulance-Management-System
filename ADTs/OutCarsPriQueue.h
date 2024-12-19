#pragma once
#include "priQueue.h"
#include "../headers/Car.h"

class OutCarsPriQueue : public priQueue<Car*>
{
public:
	using priQueue<Car*>::priQueue; //inheriting Base constructor
	Car* cancelRequest(int pid);
	void print();
	Car* GetRandomOutCarToFail();
};
