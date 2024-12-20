#include "../headers/Hospital.h"
#include "../headers/Organiser.h"
#include <iostream>

Hospital::Hospital(Organiser* organiser, int id) : organiser(organiser) , hospitalID(id)
{}

Hospital::~Hospital()
{
    Car* c = nullptr;
    while (freeNormalCars.dequeue(c))
    {
        if (c)
            delete c;
    }
    while (freeNormalCars.dequeue(c))
    {
        if (c)
            delete c;
    }
}
LinkedQueue<Car*>& Hospital::GetFreeSpecialCars() {
    return freeSpecialCars;
}

LinkedQueue<Car*>& Hospital::GetFreeNormalCars() {
    return freeNormalCars;
}
void Hospital::addpatient(Patient* t) {
    switch (t->GetType()) {
    case NP:
        npQueue.enqueue(t);
        break;
    case SP:
        spQueue.enqueue(t);
        break;
    case EP:
        epQueue.enqueue(t, t->GetSeverity());
        break;
    }
}

Patient* Hospital::removepatient(int pid)
{
   return npQueue.cancelRequest(pid);
}

void Hospital::Assignpatient() {   //ay 7aga for now idk el switch case
        AssignEP();
        AssignSP();
        AssignNP();
}

void Hospital::LoadCars(int sCars, int nCars)
{
    for (int i = 0; i < sCars; i++)
    {
        Car* c = new Car(CAR_TYPE::SPECIAL_CAR, hospitalID, i);
        freeSpecialCars.enqueue(c);
    }

    for (int i = 0; i < nCars; i++)
    {
        Car* c = new Car(CAR_TYPE::NORMAL_CAR, hospitalID, i);
        freeNormalCars.enqueue(c);
    }
}

void Hospital::CarBack(Car* car)
{
    if (car->GetType() == CAR_TYPE::NORMAL_CAR)
    {
        freeNormalCars.enqueue(car);
    }
    else
    {
        freeSpecialCars.enqueue(car);
    }
}

Car* Hospital::OutCar(CAR_TYPE type)
{
    Car* toreturn = nullptr;
    if (type == CAR_TYPE::SPECIAL_CAR)
        freeSpecialCars.dequeue(toreturn);
    else
        freeNormalCars.dequeue(toreturn);
    return toreturn;
}

Patient* Hospital::FinishSP()
{
    Patient* toreturn = nullptr;
    spQueue.dequeue(toreturn);
    return toreturn;
}

Patient* Hospital::FinishEP()
{
    Patient* toreturn = nullptr;
    int pri = -1;
    epQueue.dequeue(toreturn, pri);
    return toreturn;
}

Patient* Hospital::FinishNP()
{
    Patient* toreturn = nullptr;
    npQueue.dequeue(toreturn);
    return toreturn;
}

ostream& operator<<(ostream& os, const Hospital& h)
{
    cout << "================= HOSPITAL #" << h.hospitalID << " data ====================" << endl;

    //EP
    cout << h.epQueue.getCount() << " EP requests: "; h.epQueue.printList(); cout << endl;

    //SP
    cout << h.spQueue.getCount() << " SP requests: "; h.spQueue.printList(); cout << endl;
    
    //NP
    cout << h.npQueue.getCount() << " NP requests: "; h.npQueue.printList(); cout << endl;

    //Free cars
    cout << "Free Cars: " << h.freeSpecialCars.getCount() << " SCars, " << h.freeNormalCars.getCount() << " NCars" << endl;

    cout << "================= HOSPITAL #" << h.hospitalID << " data end ====================" << endl;

    return os;
}


void Hospital::AssignNP() {
    Patient *p = nullptr;
    Car* c=nullptr;
    if (!npQueue.isEmpty() && !freeNormalCars.isEmpty())
    {
        npQueue.dequeue(p);

        freeNormalCars.dequeue(c);

        c->AssignPatient(p,p->GetRequestTime());
        return;

    }
    else if(!npQueue.isEmpty() && freeNormalCars.isEmpty())
    {
        npQueue.dequeue(p);

        freeSpecialCars.dequeue(c);

        c->AssignPatient(p, p->GetRequestTime());

    }
    return;
}

void Hospital::AssignSP() {
    Patient* p = nullptr;
    Car* c = nullptr;
    if (!spQueue.isEmpty() && !freeSpecialCars.isEmpty())
    {

        spQueue.dequeue(p);

        freeSpecialCars.dequeue(c);

        c->AssignPatient(p, p->GetRequestTime());
        return;
    }
    else if (!spQueue.isEmpty() && !freeNormalCars.isEmpty())
    {
        spQueue.dequeue(p);
        
        freeNormalCars.dequeue(c);
        
        c->AssignPatient(p,p->GetRequestTime());
        return;
    }
    return;
}
void Hospital::AssignEP() {
    Patient* p = nullptr;
    Car* c = nullptr;
    int pri;

    if (!epQueue.isEmpty() && !freeNormalCars.isEmpty())
    {
        epQueue.dequeue(p,pri);

        freeNormalCars.dequeue(c);

        c->AssignPatient(p, p->GetRequestTime());
        return;

    }
    else if (!epQueue.isEmpty() && freeNormalCars.isEmpty())
    {
        epQueue.dequeue(p, pri);

        freeSpecialCars.dequeue(c);

        c->AssignPatient(p, p->GetRequestTime());
        return;
    }
    else
    {
        organiser->Sendpatient(p,p->getDistance());
    }
}
