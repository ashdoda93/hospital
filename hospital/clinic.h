#ifndef CLINIC_H
#define CLINIC_H
//written with chatGPT with ideal structure format
#include <string>
#include "queue.h"

class Clinic {
private:
    std::string name;
    Queue patientQueue;

public:
    Clinic(const std::string& clinicName);
    bool addPatient(const std::string& firstName, const std::string& lastName, const std::string& ssn);
    bool addCriticalPatient(const std::string& firstName, const std::string& lastName, const std::string& ssn);
    bool operatePatient();
    bool cancelPatient(const std::string& ssn);
    void listPatients() const;
    const std::string& getName() const;
    Queue* getQueue();
    bool isFull() const;

};

#endif 