#pragma once
#include "LinkedQueue.h"
#include "../headers/Patient.h"

class NPatientQueue : public LinkedQueue<Patient*>
{
public:
	using LinkedQueue<Patient*>::LinkedQueue; //inheriting Base constructor
	Patient* cancelRequest(int pid);
	void print();
};