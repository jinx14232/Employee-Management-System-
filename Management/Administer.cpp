#include"Administer.h"

Employee* Administer::getEmployee(int idx)
{
	return (employees+idx);
}

void Administer::display() {
	cout << "\n\tDepartment: " << department;
	cout << "\n\tID: " << id;
	cout << "\n\tNAME: " << name;
	cout << "\n\tMAIL: " << mail;
	cout << "\n\tPASSWORD: " << password;
	cout << "\n\tHIRING MADE: " << hiringMade;
}
