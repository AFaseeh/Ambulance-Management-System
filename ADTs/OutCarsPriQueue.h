#pragma once
#include "priQueue.h"
#include "../headers/Car.h"

class OutCarsPriQueue : public priQueue<Car*>
{
public:
	using priQueue<Car*>::priQueue; //inheriting Base constructor
	Car* cancelRequest(int pid);
	void print();
};

inline Car* OutCarsPriQueue::cancelRequest(int pid)
{
	int trashcan = -1;
	priNode<Car*>* p = head;
	Car* car = nullptr;
	// Empty
	if (isEmpty())
		return nullptr;
	// First priNode
	if (head->getItem(trashcan)->GetAssignedPatientID() == pid)
	{
		priNode<Car*>* todelete = head;
		head = head->getNext();
		delete todelete;
		return (p->getItem(trashcan));
	}

	while (p->getNext())
	{
		if (p->getNext()->getItem(trashcan)->GetAssignedPatientID() == pid)
		{
			priNode<Car*>* todelete = p->getNext();
			car = p->getNext()->getItem(trashcan);
			p->setNext(p->getNext()->getNext());
			delete todelete;
			return car;
		}
		p = p->getNext();
	}

	return nullptr;
}

inline void OutCarsPriQueue::print()
{
	priNode<Car*>* p = this->head;
	int trashcan;
	while (p)
	{
		std::cout << "ID: " << p->getItem(trashcan)->GetAssignedPatientID() << std::endl;
		p = p->getNext();
	}
}
