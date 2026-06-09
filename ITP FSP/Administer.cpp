#include"Administer.h"

Employee* Administer::getEmployee(int idx)
{
	return (employees+idx);
}

void Administer::assignTask(Employee* emp)
{
	string task, instruction;
	int dueDate;
	
	cout << "\n\tEnter task: ";
	cin.ignore();
	getline(cin, task);
	cout << "\n\tEnter instruction: ";
	getline(cin, instruction);
	cout << "\n\tEnter due date: ";
	cin >> dueDate;
	WorkLoad wl(task, dueDate, instruction);
	emp->addTask(wl);

}

void Administer::display() {
	cout << "\n\tDepartment: " << department;
	cout << "\n\tID: " << id;
	cout << "\n\tNAME: " << name;
	cout << "\n\tMAIL: " << mail;
	cout << "\n\tPASSWORD: " << password;
	cout << "\n\tHIRING MADE: " << hiringMade;
}
