#pragma once

#include<iostream>
#include<string>


void empMenu(Company& company, int empIdx);

void employment(Company &company) {
	string credential; // pass
	cout << "\n\tEnter password: ";
	cin.ignore();
	getline(cin, credential);

	int empIdx = company.findEmp(credential);

	if (empIdx == -1) {
		cout << "\n\tSorry! No employee found with this credential!!\n";
		hold("Press any key to continue: ");
		return;
	}
	system("CLS");
	empMenu(company, empIdx);

}
void empMenu(Company& company, int empIdx) {
	Employee *user = company.getEmp(empIdx);

	int ch;
	do {
		cout << "\n\n\t\t-----DASHBOARD-----\n";
		cout << "\n\t1. View Profile";
		cout << "\n\t2. Work Load";
		cout << "\n\t3. G-Mail";
		cout << "\n\t4. Mark Attendance";
		cout << "\n\t5. Salary Information";
		cout << "\n\t6. Log Out";
		cout << "\n\n\tEnter choice: ";
		cin >> ch;
		validateInput(ch, 8);
		system("CLS");
		switch (ch) {
		case 1:
			cout << "\n--------------------------------------\n";
			user->display();
			cout << "\n\n--------------------------------------\n";
			hold("Press any key to continue: ");
			break;
		case 2: 
		{
			user->showWorkLoad();
		}
		break;
		case 3:
		{
			int ch;
			do
			{
				cout << "\n\t-----Gmail-----\n";
				cout << "\t1. Compose\n";
				cout << "\t2. Inbox\n";
				cout << "\t3. Exit\n";

				cin >> ch;
				validateInput(ch, 3);
				system("CLS");
				switch (ch)
				{
				case 1:
				{
					string mail;
					cout << "\n\tEnter mail of receiver: ";
					cin.ignore();
					getline(cin, mail);
					if (mail == user->getMail()) {
						cout << "\n\tYou cannot send mail to yourself!!\n";
						hold("Press any key to continue: ");
						break;
					}
					bool sent = company.sendMail(user, mail);
					if (sent) {
						cout << "\n\tMail sent successfully!!\n";
						hold("Press any key to continue: ");
					}
					else {
						cout << "\n\tFailed to send mail!! Check the mail and try again.\n";
						hold("Press any key to continue: ");
					}

				}
				break;
				case 2:
					user->showMails();
				break;
				}

			} while (ch != 3);

		}break;
		case 4: 
		{

		break;
		}
		case 5: //salary detail
		{
			//int dptNo = findDpt(user->department);
			//dpts dpt = adm_departments[dptNo];
			//cout << "\n\t\t----SALARY DETAILS----\n";
			//cout << "\n\tDepartment Salary: " << dpt.salary;
			//cout << "\n\tAssigned Salary: " << user->salary;
			//cout << "\n\tMonthly Attendance: " << user->p;
			//cout << "\n\tCurrent Salary: " << (float(user->p) / 30) * user->salary;
			//cout << "\n\n-----------------------------------------";
			//cout << "\n\n\tYour Current Salary is calculated bases on your preformance.\n\tIf you have any quiries related to your Assigned salary,\n\tYou can register request to your eymployer\n";
			//hold();
			break;
		}
		case 6:
			return;
			break;
		}
	} while (1);



}