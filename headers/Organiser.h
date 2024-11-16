#pragma once
#ifndef ORGANISER_H
#define ORGANISER_H

class Hospital;

class Organiser {
public:
    Organiser(int size);
    ~Organiser();
    void addHospital(Hospital* hospital);
    Hospital* getHospital(int index);
    int getHospitalCount();

private:
    int capacity;
    int count;
    Hospital** hospitals;  
};
#endif // ORGANISER_H
