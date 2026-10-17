#pragma once
#include "patient.h"
#include "Doctors.h"

class HospitalSimulator {
private:
    int totalDoctors;
    int totalPatients;
    int currentTime;

    Doctor* doctors;
    Patient* patients;

public:
    HospitalSimulator(); 
    HospitalSimulator(int totalDoctors, int totalPatients, int currentTime); 
    void simulate();
    void inputFile(const string& filename);
    ~HospitalSimulator();
};