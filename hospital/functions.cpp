#include "Header.h"
//Wrtitten with chatGPT using previous code as prompt

void departmentMenu(Clinic* clinic, ofstream& log) {
    int choice;
    do {
        cout << "\n--- " << clinic->getName() << " Menu ---" << endl;
        cout << "1. Add New Patient\n2. Add Critically Ill Patient\n3. Operate on Patient\n4. Cancel Patient\n5. List All Current Patients\n6. Exit to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string firstName, lastName, ssn;
        switch (choice) {
        case 1:
            cout << "First Name: "; getline(cin, firstName);
            cout << "Last Name: "; getline(cin, lastName);
            cout << "SSN: "; getline(cin, ssn);
            if (ssn.empty() || !isNumeric(ssn)) {
                log << "ERROR: Invalid or missing SSN for patient: " << firstName << " " << lastName << endl;
                break;
            }
            if (clinic->addPatient(firstName, lastName, ssn)) {
                log << clinic->getName() << " Patient (Regular): " << firstName << " " << lastName << " was added to the waiting room." << endl;
            }
            else {
                log << "ERROR: " << clinic->getName() << " is full. Could not add " << firstName << " " << lastName << endl;
                cout << "ERROR: " << clinic->getName() << " is full. Could not add " << firstName << " " << lastName << endl;
            }
            break;
        case 2:
            cout << "First Name: "; getline(cin, firstName);
            cout << "Last Name: "; getline(cin, lastName);
            cout << "SSN: "; getline(cin, ssn);
            if (ssn.empty() || !isNumeric(ssn)) {
                log << "ERROR: Invalid or missing SSN for critical patient: " << firstName << " " << lastName << endl;
                break;
            }
            if (clinic->addCriticalPatient(firstName, lastName, ssn)) {
                log << clinic->getName() << " Patient (Critical): " << firstName << " " << lastName << " was added to the waiting room." << endl;
            }
            else {
                log << "ERROR: " << clinic->getName() << " is full. Could not add " << firstName << " " << lastName << endl;
                cout << "ERROR: " << clinic->getName() << " is full. Could not add " << firstName << " " << lastName << endl;
            }
            break;
        case 3:
            if (clinic->operatePatient()) {
                // already prints in operatePatient
            }
            break;
        case 4:
            cout << "Enter SSN: "; getline(cin, ssn);
            if (!clinic->cancelPatient(ssn)) {
                log << "ERROR: Unable to find patient: " << ssn << " in the " << clinic->getName() << endl;
            }
            else {
                log << clinic->getName() << " Patient with SSN " << ssn << " was removed from the waiting list." << endl;
            }
            break;
        case 5:
            clinic->listPatients();
            break;
        case 6:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);
}
//Written with chatGPT using previous code as prompt and the need to keep a list of records
void exportRemainingPatients(const map<string, Clinic*>& clinics, const string& filename) {
    // Create filename with current date
    time_t now = time(0);
    tm localTime;
    if (localtime_s(&localTime, &now) != 0) {
        cerr << "ERROR: Failed to get local time." << endl;
        return;
    }
    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &localTime);
    string datedFilename = "next_day_" + string(dateStr) + ".csv";

    // Open the file using the dated filename
    ofstream outFile(datedFilename);
    if (!outFile.is_open()) {
        cerr << "ERROR: Could not open " << datedFilename << " for writing remaining patients." << endl;
        return;
    }

    for (std::map<std::string, Clinic*>::const_iterator it = clinics.begin(); it != clinics.end(); ++it) {
        const std::string& name = it->first;
        Clinic* clinic = it->second;

        std::string code;
        if (name == "Heart Clinic") code = "HC";
        else if (name == "Pulmonary Clinic") code = "PC";
        else if (name == "Plastic Surgery Clinic") code = "PSC";
        else code = "UNK";

        Queue* q = clinic->getQueue();
        Queue::Node* current = q->getFront();

        while (current) {
            const Patient& p = current->data;
            outFile << code << "," << p.firstName << "," << p.lastName << "," << p.ssn << "," << (p.status == CRITICAL ? "C" : "R") << endl;
            current = current->next;
        }
    }
    outFile.close();
}

