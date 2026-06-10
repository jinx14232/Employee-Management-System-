#include"Employee.h"
#include"utilities.h"

void Employee::showWorkLoad()
{
	if (workLoad.empty()) {
		cout << "\n\tNo tasks assigned yet!";
		return;
	}
	cout << "\n\t------WORKLOAD-----\n\n";
	for (int i = 0; i < workLoad.size(); i++) {
		WorkLoad wl = workLoad[i];
		cout << "\n\t\t---Task No. " << i + 1 << "--\n";
		cout << "\n\tTask: " << wl.getTask()
			<< "\n\tInstruction: " << wl.getInstruction()
			<< "\n\tDue Date: " << wl.getDueDate() << endl;
	}
	hold("Press any key to continue: ");
}

void Employee::display()
{
	cout << "\n\tDepartment: " << department;
	cout << "\n\tID: " << id;
	cout << "\n\tNAME: " << name;
	cout << "\n\tMAIL: " << mail;
	cout << "\n\tPASSWORD: " << password;
	cout << "\n\tSALARY: " << salary;
	cout << "\n\tADMIN ID: " << adminId;
	cout << "\n\tEMPLOYER: " << admin;
	cout << "\n\tADMIN MAIL: " << adminMail;
}