#ifndef DOCTORS_H
#define DOCTORS_H
using namespace std;
#include <string>
class Doctor {
private:
    int id;
    string name;
    int specialization;
	bool isBusy;
public:
	Doctor(int id, string name, int specialization) : id(id), name(name), specialization(specialization),  isBusy(false) {}
    Doctor() {
    }
};
#endif