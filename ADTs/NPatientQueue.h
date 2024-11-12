#pragma once
#include "LinkedQueue.h"
#include "../Patient.h"

class NPatientQueue : public LinkedQueue<Patient*>
{
public:
	using LinkedQueue<Patient*>::LinkedQueue; //inheriting Base constructor
	Patient* cancelRequest(int pid);
	void print();
};

Patient* NPatientQueue::cancelRequest(int pid)
{
	Node<Patient*>* p = frontPtr;
	Patient* patient = nullptr;
	// Empty
	if (isEmpty())
		return nullptr;
	// First node
	if (frontPtr->getItem()->GetID() == pid)
	{
		Node<Patient*>* todelete = frontPtr;
		frontPtr = frontPtr->getNext();
		delete todelete;
		return (p->getItem());
	}

	while (p->getNext())
	{
		if (p->getNext()->getItem()->GetID() == pid)
		{
			Node<Patient*>* todelete = p->getNext();
			patient = p->getNext()->getItem();
			p->setNext(p->getNext()->getNext());
			delete todelete;
			return patient;
		}
		p = p->getNext();
	}

	return nullptr;
}


inline void NPatientQueue::print()
{
	Node<Patient*>* p = frontPtr;
	while (p)
	{
		std::cout << "ID: " << p->getItem()->GetID() << std::endl;
		p = p->getNext();
	}
}