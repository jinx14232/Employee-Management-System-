#pragma once
#include<iostream>
#include<string>
#include"Mail.h"
#include<vector>
//#include"utilities.h"

using namespace std;
class Company;
class Person
{
protected:
	string name;
	string department;
	string id;
	string mail;
	string password;
	vector <Mail> inbox;
public:
	Person() {};
	Person(string n, string d, string i, string m, string p) {
		name = n;
		department = d;
		id = i;
		mail = m;
		password = p;
	}
	string getName() {
		return name;
	}
	string getDepartment() {
		return department;
	}
	string getId() {
		return id;
	}
	string getPassword() {
		return password;
	}
	string getMail() {
		return mail;
	}
	void receiveMail(Mail mail) {
		inbox.push_back(mail);
	}
	Mail getInbox(int idx) {
		return inbox[idx];
	}
	vector<Mail> getAllInbox() {
		return inbox;
	}
	void showMail(int idx) {
		
		//cout << "\n\t------INBOX-----\n\n";
		//for (int i = 0; i < inbox.size(); i++) {
		//	Mail mail = inbox[i];
		cout << "\n\tSender: " << inbox[idx].getSender()
				<< "\n\tReceiver: " << inbox[idx].getReceiver()
				<< "\n\tSubject: " << inbox[idx].getSubject()
				<< "\n\n\tBody: " << inbox[idx].getBody() << endl;
	}
	Mail getMail(int idx) {
		return inbox[idx];
	}
    void mailMenu(Company& company);
	virtual void display() = 0;

};

