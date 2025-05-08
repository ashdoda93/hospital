#include <string>
#include <map>
#include <fstream>
#include <set>
#include "clinic.h"

bool isNumeric(const std::string& str);


void loadInitialPatients(const string& filename, map<string, Clinic*>& clinics, ofstream& transactionLog, set<string>& seenSSNs);

