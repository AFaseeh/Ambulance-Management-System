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

	toAddCar->SetCheckUpTimeFinish(currentTime);
	int finishCheckup = toAddCar->GetCheckUpTimeFinish();

	enqueue(toAddCar, -(finishCheckup));
}

Car* CheckUpQueue::ReturnCarFromCheckUp(int currentTime)
{
	Car* c = nullptr;
	int pri = -1;
	if (isEmpty() == false && peek(c, pri) && c->GetCheckUpTimeFinish() == currentTime)
	{
		dequeue(c, pri);
	}
	else
	{
		c = nullptr;
	}

	return c;
}
