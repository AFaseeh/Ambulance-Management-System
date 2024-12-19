#pragma once
#include "../ADTs/LinkedQueue.h"
#include "../ADTs/OutCarsPriQueue.h"
#include "../headers/UI.h"
#include "Hospital.h"

//#include "../records.h"

#include "../ADTs/ArrayStack.h"


#include "CancelRequest.h"
enum Operationmode {
    INTERACTIVE_MODE,
SILENT_MODE


};

class Organiser {
private:
    int** distanceMatrix;
    int hospitalNumber;
    int numOfRequests;
    int totalbusytime;
    UI* ui;
    Hospital** hospitals;		// Array of pointers to Hospital objects
    OutCarsPriQueue OutCars;
    priQueue<Car*> BackCars;
    LinkedQueue<CancelRequest*> CancelledRequest;
    LinkedQueue<Patient*> FinishedRequest;

    LinkedQueue<Patient*> AllPatients;

public:
    Organiser();
    ~Organiser();
    //void sortrecords(LinkedQueue<record*>& r);

    void UpdateTimeStep(int time,int mode);		// Gets called Every timestep
    void LoadFile();					// Loads file at program startup
    void Addout_Car(Car* car, int CurrentStep);			//											**
    void SwitchOutToBack(int time);				// Puts front of "Outcars" into "Backcars"	**
    void AddPatient(Patient* patient);	// add patient to allPatients queue			**
    void returnCar(int CurrentStep);			//											**
    void cancelRequest(int timestep);	//											**

    // Collect statistics that are needed to create output file
    void PrintInfo();

    //Phase 1.2
    void SimulatorFunc();
    void GenerateOutputFile(int timestep);
    void TestGenerateOutputFile(int timestep);

    void SendPatientsToHospital(int time);

    //phase2

    void Sendpatient(Patient* p, int distance);
   

};