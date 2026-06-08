#pragma once
#include "Person.h"
#include "Employee.h"
#include <vector>

class Mail;

class Administer :
	public Person
{
private:
	int maxEmp = 3;
	int hiringMade= 0;
	Employee employees[3];
public:
	Administer(string n, string d, string i, string m, string p) {
		name = n;
		department = d;
		id = i;
		mail = m;
		password = p;
		hiringMade = 0;
	}
	Administer() {}

	void incrementHiringMade() {
		hiringMade++;
	}
	//getters
	int getHiringMade() {
		return hiringMade;
	}
	Employee* getEmployee(int idx);
	void display() override;

};

