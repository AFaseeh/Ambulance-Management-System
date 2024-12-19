#pragma once
#include "priQueue.h"
#include "../headers/Patient.h"

class EPatientQueue : public priQueue<Patient*>
{
public:
	using priQueue<Patient*>::priQueue; //inheriting Base constructor
	void InsertAtBeginning(Patient* p);
};