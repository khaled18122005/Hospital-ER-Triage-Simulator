#include "HospitalSimulator.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 1. Default Constructor
HospitalSimulator::HospitalSimulator() {
    totalDoctors = 0;
    totalPatients = 0;
    currentTime = 0;
    doctors = nullptr;
    patients = nullptr;
}

// 2. Parameterized Constructor
HospitalSimulator::HospitalSimulator(int totalDoctors, int totalPatients, int currentTime) {
    this->totalDoctors = totalDoctors;
    this->totalPatients = totalPatients;
    this->currentTime = currentTime;

    // حجز مساحة ديناميكية في الذاكرة
    doctors = new Doctor[totalDoctors];
    patients = new Patient[totalPatients];
}

// 3. Simulation Function
void HospitalSimulator::simulate() {
    cout << "Starting Hospital ER & Triage Simulation..." << endl;
}

// 4. Input File Function
void HospitalSimulator::inputFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open input file!" << endl;
        return;
    }

    int totalDocs;
    file >> totalDocs;
    cout << "Total Doctors: " << totalDocs << endl;

    for (int i = 0; i < totalDocs; i++) {
        int id, spec;
        string name;
        file >> id >> name >> spec;
        cout << "Loaded Doctor: " << name << endl;
    }

    int totalPats;
    file >> totalPats;
    cout << "Total Patients: " << totalPats << endl;

    for (int i = 0; i < totalPats; i++) {
        int id, arrival, priority, treatment;
        file >> id >> arrival >> priority >> treatment;
        cout << "Loaded Patient ID: " << id << " with Priority: " << priority << endl;
    }

    file.close();
    cout << "Input file loaded successfully!" << endl;
}

// 5. Destructor
HospitalSimulator::~HospitalSimulator() {
    delete[] doctors;
    delete[] patients;
    cout << "Hospital Simulator resources cleaned up successfully." << endl;
}