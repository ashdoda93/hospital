#include <fstream>
#include "clinic.h"

void departmentMenu(Clinic* clinic, std::ofstream& log);
void exportRemainingPatients(const std::map<std::string, Clinic*>& clinics, const std::string& fileName);

