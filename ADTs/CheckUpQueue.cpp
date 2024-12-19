#include "CheckUpQueue.h"
#define DEFAULTCHECKUPTIME 2


CheckUpQueue::CheckUpQueue()
	:checkupTime (DEFAULTCHECKUPTIME) // default
{
}

void CheckUpQueue::SetCheckUpTime(int time)
{
	checkupTime = time;
}

void CheckUpQueue::AddCarToCheckUp(Car* toAddCar, int currentTime)
{
	if (toAddCar == nullptr)
		return;

	toAddCar->SetStatus(CAR_STATUS::IN_CHECKUP);


	enqueue(toAddCar);
	toAddCar->SetCheckUpTimeFinish(currentTime, checkupTime);
}

Car* CheckUpQueue::ReturnCarFromCheckUp(int currentTime)
{
	Car* c = nullptr;
	if (peek(c) && c->GetCheckUpTimeFinish() == currentTime)
	{
		dequeue(c);
	}

	return c;
}
