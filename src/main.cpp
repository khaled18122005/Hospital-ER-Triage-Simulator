#include <iostream>
#include "Node.h"

using namespace std;

int main() {
    cout << "=== Hospital ER & Triage Simulator ===" << endl;

    Node<int> testPatient(101, 5);
    cout << "Test Patient ID: " << testPatient.getItem()
        << " | Severity Priority: " << testPatient.getPriority() << endl;

    return 0;
}