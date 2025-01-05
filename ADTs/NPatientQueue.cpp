#include "NPatientQueue.h"

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
		if (todelete == backPtr)
			backPtr = nullptr;
		patient = todelete->getItem();
		delete todelete;
		count--;
		return patient;
	}

	while (p && p->getNext())
	{
		Node<Patient*>* nextNode = p->getNext();
		if (nextNode->getItem()->GetID() == pid)
		{
			Node<Patient*>* todelete = nextNode;
			if (todelete == backPtr)
				backPtr = p;

			patient = todelete->getItem();
			p->setNext(todelete->getNext());
			delete todelete;
			count--;
			return patient;
		}
		p = p->getNext();
	}

	return nullptr;
}


void NPatientQueue::print()
{
	Node<Patient*>* p = frontPtr;
	while (p)
	{
		std::cout << "ID: " << p->getItem()->GetID() << std::endl;
		p = p->getNext();
	}
}

void NPatientQueue::InsertAtBeginning(Patient* p)
{
	Node<Patient*>* newNodePtr = new Node<Patient*>(p);

	if (isEmpty())
	{
		frontPtr = newNodePtr; // The queue is empty
		backPtr = newNodePtr;
		count++;
	}
	else 
	{
		newNodePtr->setNext(frontPtr);	// The queue was not empty
		frontPtr = newNodePtr;
		count++;
	}

	count++;
	return;
}
