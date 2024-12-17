#include <iostream>
#include "../ADTs/NPatientQueue.h"
#include "../ADTs/OutCarsPriQueue.h"
#include "../headers/Patient.h"
#include "../headers/Organiser.h"


void Test_NPatientQueue() 
{
	// Testing
	Patient* p1 = new Patient(PATIENT_TYPE::NP, 1, 1, 1, 1);
	Patient* p2 = new Patient(PATIENT_TYPE::NP, 2, 1, 1, 1);
	Patient* p3 = new Patient(PATIENT_TYPE::NP, 3, 1, 1, 1);
	Patient* p4 = new Patient(PATIENT_TYPE::NP, 4, 1, 1, 1);
	Patient* p5 = new Patient(PATIENT_TYPE::NP, 5, 1, 1, 1);
	Patient* p6 = new Patient(PATIENT_TYPE::NP, 6, 1, 1, 1);

	NPatientQueue q;
	q.enqueue(p1);
	q.enqueue(p2);
	q.enqueue(p3);
	q.enqueue(p4);
	q.enqueue(p5);
	q.enqueue(p6);
	q.print();
	std::cout << "*******************" << endl;
	q.cancelRequest(3);
	q.print();
	std::cout << "*******************" << endl;
	q.cancelRequest(1);
	q.print();
	std::cout << "*******************" << endl;
	q.cancelRequest(6);
	q.print();
	std::cout << "*******************" << endl;
	return;
}
void Test_OutCarsPriQueue()
{
	Car* c1 = new Car(CAR_TYPE::NORMAL_CAR, 1, -1);
	Car* c2 = new Car(CAR_TYPE::NORMAL_CAR, 1, -1);
	Car* c3 = new Car(CAR_TYPE::NORMAL_CAR, 1, -1);
	Car* c4 = new Car(CAR_TYPE::NORMAL_CAR, 1, -1);
	Car* c5 = new Car(CAR_TYPE::NORMAL_CAR, 1, -1);
	Car* c6 = new Car(CAR_TYPE::NORMAL_CAR, 1, -1);
	Patient* p1 = new Patient(PATIENT_TYPE::NP, 1, 1, 1, 1);
	Patient* p2 = new Patient(PATIENT_TYPE::NP, 2, 1, 1, 1);
	Patient* p3 = new Patient(PATIENT_TYPE::NP, 3, 1, 1, 1);
	Patient* p4 = new Patient(PATIENT_TYPE::NP, 4, 1, 1, 1);
	Patient* p5 = new Patient(PATIENT_TYPE::NP, 5, 1, 1, 1);
	Patient* p6 = new Patient(PATIENT_TYPE::NP, 6, 1, 1, 1);

	/*c1->AssignPatient(p1);
	c2->AssignPatient(p2);
	c3->AssignPatient(p3);
	c4->AssignPatient(p4);
	c5->AssignPatient(p5);
	c6->AssignPatient(p6);*/\

	OutCarsPriQueue q;
	q.enqueue(c1, 0);
	q.enqueue(c2, 0);
	q.enqueue(c3, 0);
	q.enqueue(c4, 0);
	q.enqueue(c5, 0);
	q.enqueue(c6, 0);

	q.print();
	std::cout << "*******************" << endl;
	q.cancelRequest(3);
	q.print();
	std::cout << "*******************" << endl;
	q.cancelRequest(1);
	q.print();
	std::cout << "*******************" << endl;
	q.cancelRequest(6);
	q.print();
	std::cout << "*******************" << endl;



}


int main()
{
	Organiser *o;
	o = new Organiser();
	o->LoadFile();
	//o->SimulatorFunc();
	o->TestGenerateOutputFile();
	return 0;
}