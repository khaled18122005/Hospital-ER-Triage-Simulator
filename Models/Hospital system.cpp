#include "Hospital system.h"
#include "../include/DataStructures/PriorityQueue.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "patient.h"
#include "Doctors.h"
#include "HospitalSimulator.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

HospitalSystem::HospitalSystem() {
    totalDoctors = 0;
    totalPatients = 0;
    currentTime = 0;
    doctors = nullptr;
    patients = nullptr;
}

HospitalSystem::~HospitalSystem() {
    delete[] doctors;
    delete[] patients;
}

void HospitalSystem::loadInputFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open input file!" << endl;
        return;
    }

    file >> totalDoctors;
    doctors = new Doctor[totalDoctors];
    for (int i = 0; i < totalDoctors; i++) {
        int id = 0, spec = 0;
        string name = "";
        file >> id >> name >> spec;
        doctors[i] = Doctor(id, name, spec);
    }

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

void HospitalSystem::displayEmergencyQueue() {
    cout << "\n--- Patients in Emergency Queue (Sorted by Priority) ---" << endl;
}

void HospitalSystem::runSimulation() {
    cout << "\n--- Starting Dynamic Hospital ER Triage Simulation ---" << endl;
    cout << "Total Patients in Queue: " << emergencyQueue.getCount() << endl;
    cout << "Total Doctors: " << totalDoctors << endl;

    srand(static_cast<unsigned int>(time(0)));
    currentTime = 0;

    while (true) {
        bool anyDoctorBusy = false;
        for (int i = 0; i < totalDoctors; i++) {
            if (doctors[i].getIsBusy()) {
                anyDoctorBusy = true;
                break;
            }
        }

        if (emergencyQueue.isEmpty() && !anyDoctorBusy) {
            break; 
        }

        cout << "\n[Real-Time - Clock Sec: " << currentTime << "]" << endl;

        for (int i = 0; i < totalDoctors; i++) {
            if (doctors[i].getIsBusy()) {
                if (currentTime >= doctors[i].getFreeAtTime()) {
                    doctors[i].setBusy(false);
                    cout << " -> Doctor " << doctors[i].getName() << " has finished treatment and is now AVAILABLE." << endl;
                }
            }
        }

        while (!emergencyQueue.isEmpty()) {
            Doctor* assignedDoctor = nullptr;
            for (int i = 0; i < totalDoctors; i++) {
                if (!doctors[i].getIsBusy()) {
                    assignedDoctor = &doctors[i];
                    break;
                }
            }

            if (assignedDoctor == nullptr) {
                cout << "   [Status] All doctors are busy! Remaining patients waiting in queue..." << endl;
                break;
            }

            Patient currentPatient;
            int priority = 0;
            emergencyQueue.dequeue(currentPatient, priority);
            assignedDoctor->setBusy(true);

            int randomBonus = rand() % 4;
            int treatmentTime = currentPatient.getTreatmentTime() + randomBonus;
            int finishTime = currentTime + treatmentTime;
            assignedDoctor->setFreeAtTime(finishTime);

            cout << "   [Assignment] Patient ID: " << currentPatient.getId()
                << " (Priority: " << priority << ")"
                << " assigned to Doctor: " << assignedDoctor->getName()
                << " (Treatment Time: " << treatmentTime << "s, finishes at sec " << finishTime << ")" << endl;
        }

        this_thread::sleep_for(chrono::seconds(1));
        currentTime++;
    }

    cout << "\n--- All Patients Treated Successfully! Simulation Completed. ---" << endl;
}