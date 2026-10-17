#ifndef PATIENT_H
#define PATIENT_H

#include <string>

using namespace std;

class Patient {
private:
    int id;
    int priority;
    int arrivalTime;
    int treatmentTime;
    int remainingTreatmentTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    string name;

public:
    Patient() : id(0), priority(0), arrivalTime(0), treatmentTime(0),
        remainingTreatmentTime(0), waitingTime(0), turnaroundTime(0), responseTime(0), name("") {
    }

    Patient(int id, int arrivalTime, int priority, int treatmentTime) {
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->priority = priority;
        this->treatmentTime = treatmentTime;
        this->remainingTreatmentTime = treatmentTime;
        this->waitingTime = 0;
        this->turnaroundTime = 0;
        this->responseTime = -1;
        this->name = "";
    }

    int getId() const { return id; }
    int getPriority() const { return priority; }
    int getArrivalTime() const { return arrivalTime; }
    int getTreatmentTime() const { return treatmentTime; }
    string getName() const { return name; }

    void setId(int id) { this->id = id; }
    void setPriority(int priority) { this->priority = priority; }
    void setArrivalTime(int arrival) { this->arrivalTime = arrival; }
    void setTreatmentTime(int treatment) {
        this->treatmentTime = treatment;
        this->remainingTreatmentTime = treatment;
    }
    void setName(const string& name) { this->name = name; }
};

#endif 