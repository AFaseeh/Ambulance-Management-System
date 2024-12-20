#include "OutCarsPriQueue.h"


Car* OutCarsPriQueue::cancelRequest(int pid)
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
		car = todelete->getItem(trashcan);
		delete todelete;
		count--;
		return car;
	}

	while (p->getNext())
	{
		if (p->getNext()->getItem(trashcan)->GetAssignedPatientID() == pid)
		{
			priNode<Car*>* todelete = p->getNext();
			car = p->getNext()->getItem(trashcan);
			p->setNext(p->getNext()->getNext());
			delete todelete;
			count--;
			return car;
		}
		p = p->getNext();
	}

	return nullptr;
}

void OutCarsPriQueue::print()
{
	priNode<Car*>* p = this->head;
	int trashcan;
	while (p)
	{
		std::cout << "ID: " << p->getItem(trashcan)->GetAssignedPatientID() << std::endl;
		p = p->getNext();
	}
}

Car* OutCarsPriQueue::GetRandomOutCarToFail()
{
	if (Car::GetStaticOutFailProbability() == 0)
		return nullptr;

	int random = rand() % 101;	// 0 -> 100
	if (random >= 0 && random <= Car::GetStaticOutFailProbability() && count > 0)
	{
		random = (rand() % this->count);
	}
	else
	{
		return nullptr;
	}

	priNode<Car*>* c = this->head;
	int index = 0;

	while (c && index < random)
	{
		c = c->getNext();
		index++;
	}

	int trashcan = -1;
	if (c)
	{
		return c->getItem(trashcan);
	}

	return nullptr;
}
