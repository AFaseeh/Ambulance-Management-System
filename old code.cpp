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