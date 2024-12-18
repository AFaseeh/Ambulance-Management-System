#include "records.h"


record::record(double ft, int pid, int qt, double wt, std::string status)
    :FT(ft), PID(pid), QT(qt), WT(wt), status(status) {
    count++;
}
int record::count = 0;

// Getter function to return FT (Finish Time)
double record::getFT() const {
    return FT;
}

// Getter function to return PID (Patient ID)
int record::getPID() const {
    return PID;
}

// Getter function to return QT (Queue Time)
int record::getQT() const {
    return QT;
}

// Getter function to return WT (Wait Time)
double record::getWT() const {
    return WT;
}

// Getter function to return the status
std::string record::getStatus() const {
    return status;
}

const int record::getcount()
{
    return count;
}

void record::setcount(int x)
{
    count = x;
}

