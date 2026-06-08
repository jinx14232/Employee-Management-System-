#include "Company.h"
#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include"Person.h"
#include"Administer.h"
#include"Employee.h"
#include"DepartmentInfo.h"
#include"utilities.h"
using namespace std;

int Company::allAdmins = 0;
int Company::allEmps = 0;

DepartmentInfo Company::departments[3] = {
	{ "Computer", "100", "10", "CS", 0, 0, 150000.0 },
	{ "Biology", "200", "20", "BIO", 0, 0, 100000.0 },
	{ "Management", "300", "30", "MANG", 0, 0, 50000.0 }
};

void Company::registerAdmin(int dptNo)
{
	if (allAdmins >= maxAdmins) {
		cout << "\n\tSorry! But we can not hire more than " << maxAdmins << " administers in the company.\n";
		return;
	}
	string name, mail, password;
	string department = departments[dptNo].getDepartment();
	string id = departments[dptNo].getCode() + "A" + departments[dptNo].getAdminIdStart();

	cout << "\n\tEnter name: ";
	getline(cin, name);

	do {
		cout << "\n\tEnter mail: ";
		getline(cin, mail);
		addAt(mail);
	} while (mailExists(mail) || !validMail(mail));

	do {
		cout << "\n\tEnter password: ";
		getline(cin, password);
	} while (passwordExists(password));

	administers[allAdmins] = Administer(name, department, id, mail, password);
	
	allAdmins++;
	departments[dptNo].increaseAdmins();
	departments[dptNo].incrementAdminId();
	
}

int Company::getDptNo(string dpt)
{
	for (int i = 0; i < 3; i++) {
		if(departments[i].getDepartment() == dpt) {
			return i;
		}
	}
	return -1;
}

bool Company::mailExists(string mail)
{
	for (int i = 0; i < allAdmins; i++) {

		if (administers[i].getMail() == mail) {
			cout << "\n\tSorry! This mail is already registered. Try another one.\n";
			return true;
		}
	}
	for (int e = 0; e < allEmps; e++) {
		if (employees[e].getMail() == mail) {
			cout << "\n\tSorry! This mail is already registered. Try another one.\n";
			return true;
		}
	}
	return false;
}

bool Company::passwordExists(string pass)
{
	for (int i = 0; i < allAdmins; i++) {
		if (administers[i].getPassword() == pass) {
			cout << "\n\tSorry! This password is already taken. Try another one.\n";
			return true;
		}
	}
	return false;
}
bool Company::passwordExists(string pass, string emp)
{
	for (int i = 0; i < allEmps; i++) {
		if (employees[i].getPassword() == pass) {
			cout << "\n\tSorry! This password is already taken. Try another one.\n";
			return true;
		}
	}
	return false;
}

void Company::insight() const
{
	cout << "\n\t------ADMINISTERS-----\n\n";
	for (int i = 0; i < allAdmins; i++) {
		Administer admin = administers[i];
		admin.display();
	}
	cout << "\n\t------EMPLOYEES-----\n\n";
	for (int i = 0; i < allEmps; i++) {
		Employee emp = employees[i];
		emp.display();
	}

}
bool Company::sendMail(Person* sender, string receiver)
{
	Person* recipient = getUserByMail(receiver);
	if(!recipient) {
		return false;
	}
	string subject, body;
	cout << "\n\tCompose Email: ";
	cout << "\n\tSender: " << sender->getMail() << sender->getName();
	cout << "\n\tReceiver: " << receiver;
	cout << "\n\tSubject: ";
	getline(cin, subject);
	cout << "\n\tBody: ";
	getline(cin, body);

	Mail mail(sender->getMail(), receiver, subject, body);
	recipient->receiveMail(mail);
	sender->receiveMail(mail); //for sent items

	return true;
}

Person* Company::getUserByMail(string mail)
{
	for (int i = 0; i < allAdmins; i++) {
		if (administers[i].getMail() == mail) {
			return &administers[i];
		}
	}
	for (int i = 0; i < allEmps; i++) {
		if (employees[i].getMail() == mail) {
			return &employees[i];
		}
	}
	return nullptr;
}
int Company::findAdmin(string pass)
{
	for (int i = 0; i < allAdmins; i++) {
		if (administers[i].getPassword() == pass) {
			return i;
		}
	}
	return -1;
}
int Company::findEmp(string pass)
{
	for (int i = 0; i < allEmps; i++) {
		if (employees[i].getPassword() == pass) {
			return i;
		}
	}
	return -1;
}
//bool Company::sendMail(Mail composedMail)
//{
//
//	return false;
//}
void Company::hireEmp(Administer* admin, DepartmentInfo* department)
{
	string name, mail, password;

	cout << "\n\tEnter name: ";
	cin.ignore();
	getline(cin, name);

	do {
		cout << "\n\tEnter mail: ";
		getline(cin, mail);
		addAt(mail);
	} while (mailExists(mail) || !validMail(mail));

	do {
		cout << "\n\tEnter password: ";
		getline(cin, password);
	} while (passwordExists(password, "emp"));

	string dpt = department->getDepartment();
	string id = department->getCode() + "E" + department->getEmpIdStart();
	double sal = department->getSalary();
	
	employees[allEmps] = Employee(name, dpt, id, mail, password,sal, admin->getId(), admin->getMail(), admin->getName());
	*admin->getEmployee(admin->getHiringMade()) = employees[allEmps];
	admin->incrementHiringMade();
	allEmps++;
	department->increaseEmps();
	department->incrementEmpId();
}


