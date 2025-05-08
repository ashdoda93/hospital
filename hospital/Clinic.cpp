#include "Header.h"
//written with chatGPT with ideal structure format
Clinic::Clinic(const std::string& clinicName) : name(clinicName) {}

bool Clinic::addPatient(const std::string& firstName, const std::string& lastName, const std::string& ssn) {
    Patient p(firstName, lastName, ssn, REGULAR);
    return patientQueue.enqueueRegular(p);
}

bool Clinic::addCriticalPatient(const std::string& firstName, const std::string& lastName, const std::string& ssn) {
    Patient p(firstName, lastName, ssn, CRITICAL);
    return patientQueue.enqueueCritical(p);
}

bool Clinic::operatePatient() {
    Patient p("", "", "", REGULAR);
    if (patientQueue.dequeue(p)) {
        cout << name << " Patient: " << p.firstName << " " << p.lastName << " was taken to the operating room." << endl;
        return true;
    }
    cout << "No more patients." << endl;
    return false;
}

bool Clinic::cancelPatient(const std::string& ssn) {
    Patient p("", "", ssn, REGULAR);
    if (patientQueue.cancelBySSN(ssn, p)) {
        cout << name << " Patient: " << p.firstName << " " << p.lastName << " was removed from the waiting list." << endl;
        return true;
    }
    cout << "ERROR " << name << ": Unable to find patient: " << ssn << " in the waiting room." << endl;
    return false;
}

void Clinic::listPatients() const {
    cout << "\n--- " << name << " Patients ---" << endl;
    patientQueue.list();
}

const std::string& Clinic::getName() const {
    return name;
}
Queue* Clinic::getQueue() {
    return &patientQueue;
}
bool Clinic::isFull() const {
    return patientQueue.isFull();
}
