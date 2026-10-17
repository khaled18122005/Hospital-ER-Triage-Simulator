#ifndef DOCTORS_H
#define DOCTORS_H

#include <string>

using namespace std;

class Doctor {
private:
    int id;
    string name;
    int specialization;
    bool isBusy;
    int freeAtTime; // الوقت الذي يصبح فيه الدكتور متاحاً مرة أخرى

public:
    Doctor(int id, string name, int specialization)
        : id(id), name(name), specialization(specialization), isBusy(false), freeAtTime(0) {
    }

    Doctor() : id(0), specialization(0), isBusy(false), freeAtTime(0), name("") {}

    // دوال الـ Getters
    bool getIsBusy() const { return isBusy; }
    string getName() const { return name; }
    int getId() const { return id; }
    int getFreeAtTime() const { return freeAtTime; }

    // دوال الـ Setters وتحديث الحالة
    void setBusy(bool busy) { isBusy = busy; }
    void setFreeAtTime(int time) { freeAtTime = time; }

    void DrAvailability(int currentTime) {
        // لو الوقت الحالي وصل أو عدى وقت انتهاء العلاج، الدكتور بيبقى فاضي
        if (currentTime >= freeAtTime) {
            setBusy(false);
        }
        else {
            setBusy(true);
        }
    }
};

#endif // DOCTORS_H