#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include"Person.h"
#include"Administer.h"
#include"Employee.h"
#include"DepartmentInfo.h"


using namespace std;

class Company
{
private:
	const int maxAdmins = 6; //all admins in the company 2 for each department
	const int maxEmps = 18; //all employees in the company 6 for each department 3 for each admin
	
	Administer administers[6];
	Employee employees[18];

public:
	static int allAdmins;
	static int allEmps;
	static DepartmentInfo departments[3];
	static int getDptNo(string dpt);

	Company() {};

	void registerAdmin(int dptNo);
	void hireEmp(Administer* admin, DepartmentInfo* department);
	bool mailExists(string mail);
	bool passwordExists(string pass);
	bool passwordExists(string pass, string emp);
	void insight()const;
	bool sendMail(Person* sender, string receiver);
	int findAdmin(string pass);
	int findEmp(string pass);

	DepartmentInfo* getDpt(int dptNo) {
		return &departments[dptNo];
	};

	//getters
	Administer* getAdmin(int adminIdx) {
		return &administers[adminIdx];
	};
	Employee* getEmp(int empIdx) {
		return &employees[empIdx];
	};
	Person* getUserByMail(string mail);
	Person* getUserByID(string id);

};

