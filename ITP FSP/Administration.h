#pragma once
#include<iostream>

void adminMenu(Company& company, int adminIdx); 

void administration(Company& company)
{
	int ch;
	do {
		cout << "\n\n\t\t-----WELCOME TO ADMINISTRATION-----\n";
		cout << "\n\t1. Register Eymployer";
		cout << "\n\t2. Set Salary of Department";
		cout << "\n\t3. Log In";
		cout << "\n\t4. End";
		cout << "\n\n\tEnter choice: ";
		cin >> ch;
		validateInput(ch, 4);
		system("CLS");
		switch (ch) {
		case 1: //Register Eymployer
		{
			int dptNo = getDptNo();
			if (dptNo == -1)
				break;
			company.registerAdmin(dptNo);
			system("CLS");
			cout << "\n\t--Registered--\n";
			company.getAdmin(Company::allAdmins - 1)->display();
			hold("\nPress any key to continue: ");
			break;
		}
		case 2: //set salary
		{
			int dptNo = getDptNo();
			if (dptNo == -1) break;

			DepartmentInfo* dpt = company.getDpt(dptNo);
			displayDpt(*dpt);

			hold("\nAn email will be sent to employees of department by changing it!");

			cout << "\n\tEnter new salary: ";
			double salary;
			cin >> salary;
			dpt->setSalary(salary);

			displayDpt(*dpt);
			hold("\nSalary updated successfully! Press any key: ");
			break;
		}
		case 3: //log in eymployer
		{
			if (Company::allAdmins == 0) {
				cout << "\n\tNo administer has been hired at the current stage!!";
				hold("Press any key to continue: ");
				break;
			}
			string credential; //can be mail or id
			cout << "\n\tEnter password: ";
			cin.ignore();
			getline(cin, credential);

			int adminIdx = company.findAdmin(credential);

			if (adminIdx == -1) {
				cout << "\n\tSorry! No administer found with this credential!!\n";
				hold("Press any key to continue: ");
				break;
			}
			system("CLS");
			adminMenu(company, adminIdx);

		}
		case 4:
			return;
			break;
		}
	} while (1);
}
void adminMenu(Company& company, int adminIdx)
{
	Administer* user = company.getAdmin(adminIdx);
	DepartmentInfo* department = company.getDpt(Company::getDptNo(user->getDepartment()));

	int ch;
	do {
		cout << "\n\n\t\t-----DASHBOARD-----\n";
		cout << "\n\t1. View Profile";
		cout << "\n\t2. Hire Eymployees";
		cout << "\n\t3. Assign Tasks";
		cout << "\n\t4. G-Mail";
		cout << "\n\t5. Eymployee List";
		cout << "\n\t6. Generate Payroll";
		cout << "\n\t7. Log Out";
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
		case 2: //Hire emp
		{
			cout << "\n\tHiring can be made only for " << user->getDepartment() << " department!\n";
			if (department->getEmployees() >= 3) {
				cout << "\n\tSorry capacity is full! Can not hire more than " << 3 << " eymployers in " << department->getDepartment() << endl;
				hold("Press any key to continue: ");
				break;
			}

			company.hireEmp(user, department);
			system("CLS");
			cout << "\n\t--Hired--\n";
			company.getEmp(Company::allEmps - 1)->display();
			hold("\nPress any key to continue: ");
		}
		break;
		case 3: { //assign task
			if (user->getHiringMade() == 0) {
				cout << "\n\tNo eymployee has been hired yet!\n";
				hold("Press any key to continue: ");
				break;
			}
			string input;
			cout << "\n\tEnter ID or MAIL of eymployee: ";
			cin.ignore();
			getline(cin, input);
			Person* emp = company.getUserByID(input);
			if (!emp) { //try to find by mail
				emp = company.getUserByMail(input);
				if (!emp) {
					cout << "\n\tCannot find any eymployer with provided credentials!!";
					hold("Press any key to continue: ");
					break;
				}

			}
			//see if we get an employee, not an emplyer
			if (Employee* employee = dynamic_cast<Employee*>(emp)) {
				//we got an employee, now check if he is hired by the user
				if (employee->getAdminId() != user->getId()) {
					cout << "\n\tSorry you have made no hiring of this employee!!";
					hold("Press any key to continue: ");
					break;
				}
				//we got the employee and he is hired by the user, now assign task
				user->assignTask(employee);
			}
			//int* idxes = findEmp(input, "id");
			//if (idxes[1] == -1) {
			//	validateMail(input);
			//	idxes = findEmp(input, "mail");
			//	if (idxes[1] == -1) {
			//		cout << "\n\tCannot find any eymployer with provided credentials!!";
			//		hold();
			//		break;
			//	}
			//}
			//if (administers[*idxes].id != user->id) {
			//	cout << "\n\tSorry you have made no hiring of this ID";
			//	hold();
			//	break;
			//}
			//assign_task(&user->eymployees[idxes[1]]);
			//adm_reg(user, "task", &user->eymployees[idxes[1]]);
			//delete[] idxes;
			//idxes = nullptr;
			break;
		}
		case 4:
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
					bool sent= company.sendMail(user, mail);
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
		case 6: //request
		{
			//int ch;
			//cout << "\n\tYour current requests are following: ";
			//for (int i = 0; i <= user->complains; i++) {
			//	cout << "\n--------------------------------------\n\n";
			//	cout << "\t" << i + 1 << ": " << "COMPLAIN: " << user->requests[i].problem;
			//	cout << "\n\t  ID: " << user->requests[i].id << setw(3) << "\t  NAME: " << user->requests[i].name << setw(3) << "\t  MAIL: " << user->requests[i].mail;
			//	int* idxes = findEmp(user->requests[i].id, "id");
			//	if (user->id != administers[*idxes].id) cout << "\t(Not your eymployee!!)";
			//	cout << "\n\n--------------------------------------\n";
			//	delete[] idxes;
			//}
			//cout << "Total Complains: " << user->complains + 1 << endl;
			//cout << "\n\tPress 0 to exit or complain No. to delete complain: ";
			//cin >> ch;
			//if (ch > 0 && ch <= user->complains + 1) {
			//	update_arr(user->requests, user->complains, ch);
			//	user->complains--;
			//	cout << "\n\tDeleted Sucessfully";
			//	hold();
			//}
			//system("CLS");
			break;
		}
		case 5://eymployee list

			if (user->getHiringMade() == 0) {
				cout << "\n\tYou hired no employees!\n";
				break;
			}

			cout << "\n\t-----You Hiring-----\n";
			for (int i = 0; i < user->getHiringMade(); i++) {
				cout << "\n\t" << i + 1 << ": " << "Name: " << user->getEmployee(i)->getName()
					<< "\tID: " << user->getEmployee(i)->getId() <<
					"\tMAIL: " << user->getEmployee(i)->getMail();
			}
			cout << endl;
			hold("Press any key to continue: ");
			break;
		
		case 7:
			return;
			break;
		}
	} while (1);
}