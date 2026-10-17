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
    // تعريف أكواد الألوان للـ Console
    const string RESET = "\033[0m";
    const string RED = "\033[31m";      // للطوارئ والحالات الحرجة (أولوية عالية)
    const string GREEN = "\033[32m";    // لدكاترة لما يخلصوا ويبقوا متاحين
    const string YELLOW = "\033[33m";   // للتنبيهات وحالة امتلاء الدكاترة
    const string CYAN = "\033[36m";     // للوقت الحالي (Clock Sec)
    const string MAGENTA = "\033[35m";  // لتوزيع وتعيين المرضى

    cout << CYAN << "\n--- Starting Dynamic Hospital ER Triage Simulation ---" << RESET << endl;
    cout << "Total Patients in Queue: " << emergencyQueue.getCount() << endl;
    cout << "Total Doctors: " << totalDoctors << endl;

    srand(static_cast<unsigned int>(time(0)));
    currentTime = 0;

    // تعريف وتصفير مصفوفة عداد المرضى لكل دكتور
    int* doctorPatientCount = new int[totalDoctors];
    for (int i = 0; i < totalDoctors; i++) {
        doctorPatientCount[i] = 0;
    }

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

        cout << CYAN << "\n[Real-Time - Clock Sec: " << currentTime << "]" << RESET << endl;

        // تحديث حالة الدكاترة
        for (int i = 0; i < totalDoctors; i++) {
            if (doctors[i].getIsBusy()) {
                if (currentTime >= doctors[i].getFreeAtTime()) {
                    doctors[i].setBusy(false);
                    cout << GREEN << " -> Doctor " << doctors[i].getName() << " has finished treatment and is now AVAILABLE." << RESET << endl;
                }
            }
        }

        // توزيع المرضى
        while (!emergencyQueue.isEmpty()) {
            Doctor* assignedDoctor = nullptr;
            int doctorIndex = -1;

            for (int i = 0; i < totalDoctors; i++) {
                if (!doctors[i].getIsBusy()) {
                    assignedDoctor = &doctors[i];
                    doctorIndex = i;
                    break;
                }
            }

            if (assignedDoctor == nullptr) {
                cout << YELLOW << "   [Status] All doctors are busy! Remaining patients waiting in queue..." << RESET << endl;
                break;
            }

            Patient currentPatient;
            int priority = 0;
            emergencyQueue.dequeue(currentPatient, priority);
            assignedDoctor->setBusy(true);

            doctorPatientCount[doctorIndex]++;

            int randomBonus = rand() % 4;
            int treatmentTime = currentPatient.getTreatmentTime() + randomBonus;
            int finishTime = currentTime + treatmentTime;
            assignedDoctor->setFreeAtTime(finishTime);

            // تمييز الحالات الخطيرة (أولوية 4 أو 5) باللون الأحمر، وباقي الحالات بالماجنتا
            if (priority >= 4) {
                cout << RED << "   [CRITICAL ASSIGNMENT] Patient ID: " << currentPatient.getId()
                    << " (Priority: " << priority << ")"
                    << " assigned to Doctor: " << assignedDoctor->getName()
                    << " (Treatment Time: " << treatmentTime << "s, finishes at sec " << finishTime << ")" << RESET << endl;
            }
            else {
                cout << MAGENTA << "   [Assignment] Patient ID: " << currentPatient.getId()
                    << " (Priority: " << priority << ")"
                    << " assigned to Doctor: " << assignedDoctor->getName()
                    << " (Treatment Time: " << treatmentTime << "s, finishes at sec " << finishTime << ")" << RESET << endl;
            }
        }

        this_thread::sleep_for(chrono::seconds(1));
        currentTime++;
    }

    cout << "\n=========================================" << endl;
    cout << GREEN << "--- Simulation Completed Successfully! ---" << RESET << endl;
    cout << "=========================================" << endl;
    cout << "Total Simulation Time Elapsed: " << currentTime << " seconds." << endl;
    cout << "\n--- Doctor Workload Statistics ---" << endl;
    for (int i = 0; i < totalDoctors; i++) {
        cout << " * Doctor " << doctors[i].getName()
            << " (ID: " << doctors[i].getId() << "): "
            << doctorPatientCount[i] << " patients treated." << endl;
    }
    cout << "=========================================" << endl;

    delete[] doctorPatientCount;
}