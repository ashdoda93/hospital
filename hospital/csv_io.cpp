#include "Header.h"
#include <string>
#include <algorithm>
#include <set>
//written with chatGPT using previous code as prompt and discription of what I wanted it to do
bool isNumeric(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

void loadInitialPatients(const string& filename, map<string, Clinic*>& clinics, ofstream& transactionLog, set<string>& seenSSNs) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string clinicCode, firstName, lastName, ssn, statusCode;
        getline(ss, clinicCode, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, ssn, ',');
        getline(ss, statusCode, ',');

        if (firstName.empty() || ssn.empty() || !isNumeric(ssn)) {
            transactionLog << "ERROR: Invalid or missing data for patient: " << firstName << " " << lastName << " with SSN: " << ssn << endl;
            continue;
        }

        if (seenSSNs.count(ssn)) {
            transactionLog << "SKIPPED DUPLICATE: " << firstName << " " << lastName << " with SSN " << ssn << endl;
            continue;
        }
        seenSSNs.insert(ssn);

        string clinicName;
        if (clinicCode == "HC") clinicName = "Heart Clinic";
        else if (clinicCode == "PC") clinicName = "Pulmonary Clinic";
        else if (clinicCode == "PSC") clinicName = "Plastic Surgery Clinic";
        else {
            transactionLog << "ERROR: Invalid clinic code for " << firstName << " " << lastName << ": " << clinicCode << endl;
            continue;
        }

        bool isCritical = (statusCode == "C");
        bool success = isCritical
            ? clinics[clinicName]->addCriticalPatient(firstName, lastName, ssn)
            : clinics[clinicName]->addPatient(firstName, lastName, ssn);

        if (success) {
            transactionLog << clinicName << " Patient (" << (isCritical ? "Critical" : "Regular") << "): " << firstName;
            if (!lastName.empty()) transactionLog << " " << lastName;
            transactionLog << " was added to the waiting room." << endl;
        }
        else {
            transactionLog << "ERROR: " << clinicName << " is full. Could not add " << firstName;
            if (!lastName.empty()) transactionLog << " " << lastName;
            transactionLog << endl;
        }
    }

    file.close();
}