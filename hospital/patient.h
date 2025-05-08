#ifndef PATIENT_H
#define PATIENT_H
//written with chatGPT with ideal structure format
#include <string>

enum Status { REGULAR, CRITICAL };

struct Patient {
    std::string firstName;
    std::string lastName;
    std::string ssn;
    Status status;

    // Parameterized constructor
    Patient(std::string f, std::string l, std::string s, Status stat)
        : firstName(f), lastName(l), ssn(s), status(stat) {
    }

    // Default constructor
    Patient() : firstName(""), lastName(""), ssn(""), status(REGULAR) {
    }
};

#endif // PATIENT_H
