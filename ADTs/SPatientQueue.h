#pragma once
#include "LinkedQueue.h"
#include "../headers/Patient.h"

class SPatientQueue : public LinkedQueue<Patient*>
{
public:
	using LinkedQueue<Patient*>::LinkedQueue; //inheriting Base constructor
	void InsertAtBeginning(Patient* p);
};