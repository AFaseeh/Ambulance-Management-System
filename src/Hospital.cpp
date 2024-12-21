#include "../headers/Hospital.h"
#include "../headers/Organiser.h"
#include <iostream>

Hospital::Hospital(Organiser* organiser, int id) : organiser(organiser),epCount(0), hospitalID(id), checkUpTimeSC(0), checkUpTimeNC(0)
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
    car->SetStatus(CAR_STATUS::READY);
    if (car->GetType() == CAR_TYPE::NORMAL_CAR)
    {
        freeNormalCars.enqueue(car);
    }
    else
    {
        freeSpecialCars.enqueue(car);
    }
}

void Hospital::FailedCarBack(Car* car, int timeStep)
{
    if (car == nullptr)
        return;

    if (car->GetStatus() == CAR_STATUS::OUT_FAILED)
    {
        CheckUpList.AddCarToCheckUp(car, timeStep);
        Patient* p = car->ReturnPatientToHospital();
        ReassignPatientToHospital(p);
        car->SetStatus(CAR_STATUS::IN_CHECKUP);
        return;
    }
}

void Hospital::CompleteCarsCheckUp(int timestep)
{
    Car* c = nullptr;
    c = CheckUpList.ReturnCarFromCheckUp(timestep);

    while (c != nullptr)
    {
        c->SetStatus(CAR_STATUS::READY);
        CarBack(c);
        c = CheckUpList.ReturnCarFromCheckUp(timestep);
    }
}

void Hospital::ReassignPatientToHospital(Patient* p)
{
    if (p == nullptr)
        return;

    switch (p->GetType())
    {
    case PATIENT_TYPE::EP:
        epQueue.InsertAtBeginning(p);
        break;
    case PATIENT_TYPE::NP:
        npQueue.InsertAtBeginning(p);
        break;
    case PATIENT_TYPE::SP:
        spQueue.InsertAtBeginning(p);
        break;
    default:
        cerr << "ReassignPatientToHospital type mismatch\n";
        break;
    }
}

Car* Hospital::OutCar(CAR_TYPE type)
{
    Car* toreturn = nullptr;
    if (type == CAR_TYPE::SPECIAL_CAR)
        freeSpecialCars.dequeue(toreturn);
    else
        freeNormalCars.dequeue(toreturn);
    toreturn->SetStatus(CAR_STATUS::ASSIGNED);
    return toreturn;
}

void Hospital::AssignHospitalPatientsToCars(int time)
{
    Car* c = nullptr;
    c = AssignEP();
    while (c != nullptr)
    {
        organiser->Addout_Car(c, time);
        c = AssignEP();
    }

    c = AssignSP();
    while (c != nullptr)
    {
        organiser->Addout_Car(c, time);
        c = AssignSP();
    }

    c = AssignNP();
    while (c != nullptr)
    {
        organiser->Addout_Car(c, time);
        c = AssignNP();
    }
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

    //Check up List
    cout << "Check Up: " << h.CheckUpList.getCount() << " "; h.CheckUpList.printList(); cout << endl;

    cout << "================= HOSPITAL #" << h.hospitalID << " data end ====================" << endl;

    return os;
}


Car* Hospital::AssignNP() {
    Patient *p = nullptr;
    Car* c=nullptr;
    if (npQueue.isEmpty() || freeNormalCars.isEmpty())
    {
        return nullptr;
    }

    npQueue.dequeue(p);

    freeNormalCars.dequeue(c);

    c->AssignPatient(p, p->GetRequestTime());
    return c;
}
Car* Hospital::AssignSP() {
    Patient* p = nullptr;
    Car* c = nullptr;
    if (spQueue.isEmpty() || freeSpecialCars.isEmpty())
    {
        return nullptr;
    }

    spQueue.dequeue(p);
    freeSpecialCars.dequeue(c);
    c->AssignPatient(p, p->GetRequestTime());

    return c;
}
Car* Hospital::AssignEP() {
    Patient* p = nullptr;
    Car* c = nullptr;
    int pri;

    if (epQueue.isEmpty())
    {
        return nullptr;
    }

    epQueue.dequeue(p, pri);

    if (!freeNormalCars.isEmpty())
    {
        freeNormalCars.dequeue(c);

        c->AssignPatient(p, p->GetRequestTime());
    }
    else if (!freeSpecialCars.isEmpty())
    {
        freeSpecialCars.dequeue(c);

        c->AssignPatient(p, p->GetRequestTime());
    }
    else
    {
        organiser->SendPatientToNearestHospital(p, p->getDistance());
        c = nullptr;
    }

    return c;
}

int Hospital::getEPcount() {

    return epCount;
}