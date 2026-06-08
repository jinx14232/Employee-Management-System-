#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include"Company.h"

using namespace std;

static void validateInput(int& ch, int range) {
	while (!(ch >= 1 && ch <= range)) {
		cout << "\n\tPlease try again in range 1 to" << range << " :";
		cin >> ch;
	}
}
static void hold(string msg) {
	cout << "\n\t" << msg;
	_getch();
	system("CLS");
}

static int getDptNo() {
	string dpt;
	cout << "\n\tEnter Department:  ";
	cin.ignore();
	getline(cin, dpt);

	int dptNo = Company::getDptNo(dpt);
	if (dptNo == -1) {
		hold("Invalid department. Try again.\n");
		return dptNo;
	}
	return dptNo;
}

inline void addAt(string &mail) {

	size_t atPos = mail.find("@gmail.com");
	if (atPos == string::npos) {
		mail += "@gmail.com";
	}
}
inline bool validMail(string mail)
{
	size_t atPos = mail.find("@gmail.com");
	string text = mail.substr(0, atPos);
	if (text.find('@') != string::npos ||
		text.find('!') != string::npos ||
		text.find('*') != string::npos ||
		text.find('&') != string::npos ||
		text.find('.') != string::npos ||
		text.find(',') != string::npos ||
		text.find('`') != string::npos) {
		cout << "\tInvalid E-mail! Either write with full format or only text. Try again: \n";
		return false;
	}

	return true;
}
static void displayDpt(DepartmentInfo dpt) {
	cout << "\n\tDepartment: " << dpt.getDepartment();
	cout << "\n\tCode: " << dpt.getCode();
	cout << "\n\tTotal Admins: " << dpt.getEmployers();
	cout << "\n\tTotal Employees: " << dpt.getEmployees();
	cout << "\n\tSalary: " << dpt.getSalary();
	cout << "\n\tCurrent Admin Id: " << dpt.getAdminIdStart();
	cout << "\n\tCurrent Employee Id: " << dpt.getEmpIdStart();
}