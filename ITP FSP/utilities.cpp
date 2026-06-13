#include "utilities.h"
#include <iostream>
#include <conio.h>
#include "Company.h"
#include "DepartmentInfo.h"

using namespace std;

void validateInput(int& ch, int range) {
    while (!(ch >= 1 && ch <= range)) {
        cout << "\n\tPlease try again in range 1 to" << range << " :";
        cin >> ch;
    }
}

void hold(string msg) {
    cout << "\n\t" << msg;
    _getch();
    system("CLS");
}

void hold() {
    cout << "\n\tPress any key to continue: ";
    _getch();
    system("CLS");
}

void hold(int stopper) {
	int ch;
    cout << "\n\tPress " << stopper << " to continue: ";
	cin >> ch;
    while (ch != stopper) {
        cout << "\n\tPlease Press " << stopper << " to continue: ";
        cin >> ch;
	}
    system("CLS");
}

Mail composeMail(string sender, string receiver)
{
    string subject, body;
    cout << "\n\tCompose Email: ";
    cout << "\n\tSender: " << sender;
    cout << "\n\tReceiver: " << receiver;
    cout << "\n\tSubject: ";
    getline(cin, subject);
    cout << "\n\tBody: ";
    getline(cin, body);
    Mail mail(sender, receiver, subject, body);
    return mail;
}

int getDptNo() {
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

void addAt(string &mail) {

    size_t atPos = mail.find("@gmail.com");
    if (atPos == string::npos) {
        mail += "@gmail.com";
    }
}

bool validMail(string mail)
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

void displayDpt(DepartmentInfo& dpt) {
    cout << "\n\tDepartment: " << dpt.getDepartment();
    cout << "\n\tCode: " << dpt.getCode();
    cout << "\n\tTotal Admins: " << dpt.getEmployers();
    cout << "\n\tTotal Employees: " << dpt.getEmployees();
    cout << "\n\tSalary: " << dpt.getSalary();
    cout << "\n\tCurrent Admin Id: " << dpt.getAdminIdStart();
    cout << "\n\tCurrent Employee Id: " << dpt.getEmpIdStart();
}

