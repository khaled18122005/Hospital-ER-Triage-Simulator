#include <iostream>
#include "../Models/HospitalSimulator.h"
using namespace std;

int main() {
    HospitalSimulator simulator;
    simulator.inputFile("../../../Input.txt"); // لو هيرجع 3 خطوات لورا عشان يلاقي الملف في المجلد الرئيسي // تأكد إن اسم الملف مطابق
    simulator.simulate ();

    return 0;
}