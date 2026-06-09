#pragma once
#include<iostream>
#include<string>
#include"Mail.h"
#include<vector>

using namespace std;
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
	void showMails() {
		if (inbox.empty()) {
			cout << "\n\tNo mails in inbox!!\n";
			return;
		}
		cout << "\n\t------INBOX-----\n\n";
		for (int i = 0; i < inbox.size(); i++) {
			Mail mail = inbox[i];
			cout << "\n\t\t---Mail No. " << i + 1<< "--\n";
			cout << "\n\tSender: " << mail.getSender()
				<< "\n\tReceiver: " << mail.getReceiver()
				<< "\n\tSubject: " << mail.getSubject()
				<< "\n\n\tBody: " << mail.getBody() << endl;
		}
	}
	virtual void display() = 0;

};

