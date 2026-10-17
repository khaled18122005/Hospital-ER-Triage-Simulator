#include "Hospital system.h"
#include "../include/DataStructures/PriorityQueue.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "patient.h"
#include "Doctors.h"
#include "HospitalSimulator.h"

using namespace std;

// Constructor الافتراضي
HospitalSystem::HospitalSystem() {
    totalDoctors = 0;
    totalPatients = 0;
    currentTime = 0;
    doctors = nullptr;
    patients = nullptr;
}

// Destructor لتنظيف الذاكرة وتجنب الـ Memory Leaks
HospitalSystem::~HospitalSystem() {
    delete[] doctors;
    delete[] patients;
}

// دالة قراءة ملف الإدخال وتعبئة البيانات وطوابير الأولوية
void HospitalSystem::loadInputFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open input file!" << endl;
        return;
    }

    // قراءة عدد الدكاترة وبياناتهم
    file >> totalDoctors;
    doctors = new Doctor[totalDoctors];
    for (int i = 0; i < totalDoctors; i++) {
        int id = 0, spec = 0;
        string name = "";
        file >> id >> name >> spec;
    }

    // قراءة عدد المرضى وبياناتهم وإدخالهم في طابور الأولوية
    file >> totalPatients;
    patients = new Patient[totalPatients];
    for (int i = 0; i < totalPatients; i++) {
        int id = 0, arrival = 0, priority = 0, treatment = 0;
        file >> id >> arrival >> priority >> treatment;

        Patient currentPatient(id, arrival, priority, treatment);

        emergencyQueue.enqueue(currentPatient, priority);
    }

    file.close();
    cout << "Hospital data loaded successfully into the system!" << endl;
}

void HospitalSystem::displayEmergencyQueue()
{
   
        cout << "\n--- Patients in Emergency Queue (Sorted by Priority) ---" << endl;

      
    
}

void HospitalSystem::runSimulation() {
    cout << "\n--- Starting Hospital ER Triage Simulation System ---" << endl;
    cout << "Total Patients in Emergency Queue: " << emergencyQueue.getCount() << endl;

    Patient currentPatient;
    int priority = 0;

    while (emergencyQueue.dequeue(currentPatient, priority)) {
        cout << "Processing Patient ID: " << currentPatient.getId() 
             << " with Priority: " << priority << endl;
    }
}