#include "Organiser.h"
#include "Hospital.h"

#include <iostream>
class Hospital;

Organiser::Organiser(int size) {
    capacity = size;
    count = 0;
    hospitals = new Hospital * [capacity];
}

Organiser::~Organiser() {
    for (int i = 0; i < count; ++i) {
        delete hospitals[i];
    }
    delete[] hospitals;
}

void Organiser::addHospital(Hospital* hospital) {
    if (count < capacity) {
        hospitals[count] = hospital;
        ++count;
    }
    else {
        std::cout << "Organiser is full, cannot add more hospitals." << std::endl;
    }
}

Hospital* Organiser::getHospital(int index) {
    if (index >= 0 && index < count) {
        return hospitals[index];
    }
    return nullptr;
}

int Organiser::getHospitalCount() {
    return count;
}
