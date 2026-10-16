#pragma once
#include "patient.h"
#include "Doctors.h"

class HospitalSimulator {
private:
    int totalDoctors;
    int totalPatients;
    int currentTime;

    // تعريف المؤشرات هنا عشان الكلاس يشوفها
    Doctor* doctors;
    Patient* patients;

public:
    HospitalSimulator(); // كونستركتور افتراضي
    HospitalSimulator(int totalDoctors, int totalPatients, int currentTime); // كونستركتور بالمتغيرات
    void simulate();
    void inputFile(const string& filename);
    ~HospitalSimulator();
};