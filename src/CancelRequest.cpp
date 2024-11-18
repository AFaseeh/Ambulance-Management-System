#include "../headers/CancelRequest.h"

CancelRequest::CancelRequest(int pid, int cancelTime, int HID)
	: pid(pid), cancelTime(cancelTime), hospitalID(HID)
{
}

int CancelRequest::getPID() const
{
	return pid;
}

int CancelRequest::getCancelTime() const
{
	return cancelTime;
}

int CancelRequest::getHID() const
{
	return hospitalID;
}
