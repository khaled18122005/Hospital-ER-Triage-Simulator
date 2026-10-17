#include <iostream>
#include "../Models/HospitalSimulator.h"
#include"../Models/Hospital system.h"
using namespace std;

int main() {
    HospitalSimulator simulator;
    HospitalSystem hospital;
    simulator.inputFile("../../../Input.txt"); 
    simulator.simulate ();

    hospital.loadInputFile("../../../Input.txt");
    hospital.runSimulation();

    return 0;
}