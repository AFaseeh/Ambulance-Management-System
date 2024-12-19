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

void Hospital::Assignpatient(Patient* t) {
    //if (!epQueue.isEmpty()) {
    //    Patient* p;
    //    Car* car;
    //    int severity;
    //    epQueue.peek(p, severity);

    //    if (!freeNormalCars.isEmpty()) {
    //        freeNormalCars.dequeue(car);
    //        car->AssignPatient(p);
    //        std::cout << "Assigned EP patient to a normal car." << std::endl;
    //    }
    //    else if (!freeSpecialCars.isEmpty()) {
    //        freeSpecialCars.dequeue(car);
    //        car->AssignPatient(p);
    //        std::cout << "Assigned EP patient to a special car." << std::endl;
    //    }
    //    else {
    //        Hospital* nextHospital = getNextHospital();
    //        if (nextHospital != nullptr) {
    //            nextHospital->addpatient(p);
    //            std::cout << "Forwarded EP request to the next hospital." << std::endl;
    //        }
    //        else {
    //            std::cout << "No hospital available to serve EP request." << std::endl;
    //        }
    //    }
    //}

    //if (!spQueue.isEmpty()) {
    //    Patient* spPatient;
    //    spQueue.peek(spPatient);

    //    if (!freeSpecialCars.isEmpty()) {
    //        Car* assignedCar;
    //        freeSpecialCars.dequeue(assignedCar);
    //        assignedCar->AssignPatient(spPatient);
    //        std::cout << "Assigned SP patient to a special car." << std::endl;
    //    }
    //    else {
    //        std::cout << "No special cars available for SP patient." << std::endl;
    //    }
    //}

    //if (!npQueue.isEmpty()) {
    //    Patient* npPatient;
    //    npQueue.peek(npPatient);

    //    if (!freeNormalCars.isEmpty()) {
    //        Car* assignedCar;
    //        freeNormalCars.dequeue(assignedCar);
    //        assignedCar->AssignPatient(npPatient);
    //        std::cout << "Assigned NP patient to a normal car." << std::endl;
    //    }
    //    else {
    //        std::cout << "No normal cars available for NP patient." << std::endl;
    //    }
    //}
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

void Hospital::FailedCarBack(Car* car, int timeStep)
{
    if (car == nullptr)
        return;

    if (car->GetStatus() == CAR_STATUS::OUT_FAILED)
    {
        CheckUpList.AddCarToCheckUp(car, timeStep);
        Patient* p = car->ReturnPatientToHospital();
        ReassignPatientToHospital(p);
        
        return;
    }
}

void Hospital::CompleteCarsCheckUp(int timestep)
{
    Car* c = nullptr;
    do
    {
        c = CheckUpList.ReturnCarFromCheckUp(timestep);
        if (c != nullptr)
            CarBack(c);
    } while (c != nullptr);
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
