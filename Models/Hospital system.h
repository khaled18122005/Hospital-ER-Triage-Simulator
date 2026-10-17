#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "patient.h"
#include "Doctors.h"
#include "../include/DataStructures/PriorityQueue.h"

using namespace std;

class HospitalSystem {
private:
    int totalDoctors;
    int totalPatients;
    int currentTime;

    Doctor* doctors;
    Patient* patients;

    PriorityQueue<Patient> emergencyQueue;
    PriorityQueue<Patient> regularQueue;

public:
    // Constructor «·«› —«÷Ì
    HospitalSystem();

    // Destructor · ‰ŸÌ› «·–«ﬂ—…
    ~HospitalSystem();

    void loadInputFile(const string& filename);
	void actionPriorityQueue(PriorityQueue<Patient>& queue, const string& queueName);
    void displayEmergencyQueue();
    void runSimulation();
};