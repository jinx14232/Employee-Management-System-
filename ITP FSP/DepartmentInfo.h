#pragma once
#include<iostream>
#include<string>
using namespace std;

class DepartmentInfo
{
private:
	string department;
	string idStarts[2]; // for emp and admin
	string dptCode;
	int employers;
	int employees;
	double salary;
public:
	DepartmentInfo() {};
	DepartmentInfo(string dpt, string adminId, string empId, string code, int admins, int emp, double sal) {
		department = dpt;
		idStarts[0] = adminId;
		idStarts[1] = empId;
		dptCode = code;
		employers = admins;
		employees = emp;
		salary = sal;
	}
	//getters
	string getDepartment() {
		return department;
	}
	string getAdminIdStart() {
		return idStarts[0];
	}
	string getEmpIdStart() {
		return idStarts[1];
	}
	string getCode() {
		return dptCode;
	}
	int getEmployers() {
		return employers;
	}
	int getEmployees() {
		return employees;
	}
	double getSalary() {
		return salary;
	}
	//setters
	void increaseAdmins() {
		employers++;
	}
	void increaseEmps() {
		employees++;
	}
	void incrementAdminId() {
		idStarts[0] = to_string(stoi(idStarts[0]) + 1);
	}
	void incrementEmpId() {
		idStarts[1] = to_string(stoi(idStarts[1]) + 1);
	}
	void setSalary(double sal) {
		salary = sal;
	}
};

