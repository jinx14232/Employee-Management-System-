#pragma once
#include "Person.h"
#include <iostream>
#include "WorkLoad.h"
#include <vector>


class Employee :
    public Person
{
private:
	double salary;
	string adminId;
	string adminMail;
	string admin;
	vector<WorkLoad> workLoad;

public:
	Employee() {};
	Employee(string n, string d, string i, string m, string p, double s, string aI, string aM, string a) {
		name = n;
		department = d;
		id = i;
		mail = m;
		password = p;
		salary = s;
		adminId = aI;
		adminMail = aM;
		admin = a;
	};
	//getters
	double getSalary() {
		return salary;
	};
	string getAdmin() {
		return admin;
	}
	string getAdminId() {
		return adminId;
	}
	string getAdminMail() {
		return adminMail;
	}	
	void addTask(WorkLoad wl) {
		workLoad.push_back(wl);
	}
	void showWorkLoad();

	void display() override;
};


