#include "Hospital.h"
#include <iostream>

Hospital::Hospital(Organiser* organizer) : organizer(organizer) {}

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

void Hospital::Assignpatient(Patient* t) {
    if (!epQueue.isEmpty()) {
        Patient* p;
        Car* car;
        int severity;
        epQueue.peek(p, severity);

        if (!freeNormalCars.isEmpty()) {
            freeNormalCars.dequeue(car);
            car->AssignPatient(p);
            std::cout << "Assigned EP patient to a normal car." << std::endl;
        }
        else if (!freeSpecialCars.isEmpty()) {
            freeSpecialCars.dequeue(car);
            car->AssignPatient(p);
            std::cout << "Assigned EP patient to a special car." << std::endl;
        }
        else {
            Hospital* nextHospital = getNextHospital();
            if (nextHospital != nullptr) {
                nextHospital->addpatient(p);
                std::cout << "Forwarded EP request to the next hospital." << std::endl;
            }
            else {
                std::cout << "No hospital available to serve EP request." << std::endl;
            }
        }
    }

    if (!spQueue.isEmpty()) {
        Patient* spPatient;
        spQueue.peek(spPatient);

        if (!freeSpecialCars.isEmpty()) {
            Car* assignedCar;
            freeSpecialCars.dequeue(assignedCar);
            assignedCar->AssignPatient(spPatient);
            std::cout << "Assigned SP patient to a special car." << std::endl;
        }
        else {
            std::cout << "No special cars available for SP patient." << std::endl;
        }
    }

    if (!npQueue.isEmpty()) {
        Patient* npPatient;
        npQueue.peek(npPatient);

        if (!freeNormalCars.isEmpty()) {
            Car* assignedCar;
            freeNormalCars.dequeue(assignedCar);
            assignedCar->AssignPatient(npPatient);
            std::cout << "Assigned NP patient to a normal car." << std::endl;
        }
        else {
            std::cout << "No normal cars available for NP patient." << std::endl;
        }
    }
}

void Hospital::cancelNPRequest(Patient* t) {
    if (t == nullptr) {
        return;
    }

    if (!npQueue.isEmpty()) {
        Patient* npPatient = nullptr;
        npQueue.dequeue(npPatient);

        if (npPatient != nullptr && npPatient->GetID() == t->GetID()) {
            returnCarToHospital(npPatient);
        }
        else {
            npQueue.enqueue(npPatient);
        }
    }
}

void Hospital::returnCarToHospital(Patient* npPatient) {
 
}

Hospital* Hospital::getNextHospital() {
    for (int i = 0; i < organizer->getHospitalCount(); ++i) {
        Hospital* hospital = organizer->getHospital(i);

        if (hospital != this && (!hospital->freeNormalCars.isEmpty() || !hospital->freeSpecialCars.isEmpty())) {
            return hospital;
        }
    }
    return nullptr;
}

