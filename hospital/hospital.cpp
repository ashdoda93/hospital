// hospital.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Header.h"
#include <set>
//Written with chatGPT using previous code as prompt
int main()
{
    map<string, Clinic*> clinics;
    clinics["Heart Clinic"] = new Clinic("Heart Clinic");
    clinics["Pulmonary Clinic"] = new Clinic("Pulmonary Clinic");
    clinics["Plastic Surgery Clinic"] = new Clinic("Plastic Surgery Clinic");

    ofstream transactionLog("transaction_log.txt");
    std::set<std::string> seenSSNs;
    loadInitialPatients("patient.csv", clinics, transactionLog, seenSSNs);
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);
    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &localTime);
    string nextDayFile = "next_day_" + string(dateStr) + ".csv";

    loadInitialPatients(nextDayFile, clinics, transactionLog, seenSSNs);


    int deptChoice;
    do {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Heart Clinic\n2. Pulmonary Clinic\n3. Plastic Surgery Clinic\n4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> deptChoice;
        cin.ignore();

        switch (deptChoice) {
        case 1:
            departmentMenu(clinics["Heart Clinic"], transactionLog);
            break;
        case 2:
            departmentMenu(clinics["Pulmonary Clinic"], transactionLog);
            break;
        case 3:
            departmentMenu(clinics["Plastic Surgery Clinic"], transactionLog);
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (deptChoice != 4);

    exportRemainingPatients(clinics, "next_day_input.csv");

    transactionLog.close();
    for (auto& clinicPair : clinics) {
        delete clinicPair.second; // Access the pointer directly using .second
    }
    return 0;
}



