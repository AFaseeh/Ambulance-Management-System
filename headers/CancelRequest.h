#pragma once
class CancelRequest
{
	int pid;
	int cancelTime;
	int hospitalID;
public:
	CancelRequest(int pid, int cancelTime, int hid);
	int getPID() const;
	int getCancelTime() const;
	int getHID() const;
};

