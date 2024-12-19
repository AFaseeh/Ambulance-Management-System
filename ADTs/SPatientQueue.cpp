#include "SPatientQueue.h"

void SPatientQueue::InsertAtBeginning(Patient* p)
{
	Node<Patient*>* newNodePtr = new Node<Patient*>(p);

	if (isEmpty())
	{
		frontPtr = newNodePtr; // The queue is empty
		backPtr = newNodePtr;
	}
	else 
	{
		newNodePtr->setNext(frontPtr);	// The queue was not empty
		frontPtr = newNodePtr; 
	}

	count++;
	return;
}
