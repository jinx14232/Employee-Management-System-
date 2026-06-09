/*
#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include"utilities.h"
using namespace std;


//departments 
//computer science
//Biology
//management
struct workLoad {
	string task;
	int dueDate;
	string instruction;
};
struct eymployee {
	string name;
	string department;
	string id;
	string mail;
	string password;
	int salary;
	int tasks;  
	workLoad* work;
	int done;// for reg
	string *reg;
	int p;
	char attendence[30];// attendance of a month
	int toDo; 
	string *toDos;
};
struct request {
	string problem;
	string id;
	string name;
	string mail;
};
const int max_eymp = 5;
struct administer {
	string name;
	string department;
	string id;
	string mail;
	string password;
	int hiring;
	eymployee eymployees[max_eymp];
	int tasks;// for reg
	string* reg;
	int complains; //no of requests
	request* requests;
	string empFile; 
};
struct dpts {
	string department;
	int eymployers;
	int eymployees;
	string idStarts[2];
	double salary;
};

//globle variables---------------------------------
dpts adm_departments[3] = {
	{"Computer", 0, 0, {"100", "50"}, 50000},
	{"Biology", 0, 0, {"200", "70"}, 100000},
	{"Management", 0, 0, {"300", "20"}, 70000}
};
const int max_adm = 2;
int all_adm_members = 0; //total administers in all departments
int all_eymps = 0;
administer administers[max_adm*3];

//administration---------------------------------------
void administration();
void adm_register();
void adm_menu(int adm);
void hire_eymp(administer*, dpts*);
void assign_task(eymployee* eymp);
void adm_reg(administer *user, string base, eymployee* eymp);
void gen_sal(administer* user, int idx);
void update_arr(request* &array, int size, int dlt);

//eymployee-----------------------------------------
void eymp_menu(int adm_idx, int eymp_idx);
void reg_req(administer* admin, eymployee user);
void eymp_reg(eymployee* user, string base, administer* admin);
void toDoList(eymployee* user);
void toDoDlt(string* &list, int size, int dlt);

//generic functions---------------------------------------
static void validateInput(int& ch, int range) {
	while (!(ch >= 1 && ch <= range)) {
		cout << "\n\tPlease try again in range 1 to" << range<< " :";
		cin >> ch;
	}
}
static void hold() {
	cout << "\n\tPress any key to continue: ";
	_getch();
	system("CLS");
}

void check(string& input, string field, string base);
static void validateMail(string& mail) {
	int index = mail.find("@gmail.com"); //-1
	string text = mail.substr(0, index);
	bool add = false;
	for (int i = 0; i < text.size(); i++) {
		while (text[i] == '@' || 
			text[i] == '!' ||
			text[i] == '*' ||
			text[i] == '&' ||
			text[i] == '.' ||
			text[i] == ' ') {
			cout << "\tInvalid E-mail! Either write with full format or only text. Try again: ";
			getline(cin, mail);
			validateMail(mail);
			add = true;
			break;
		}
		if (add) break;
	}
	if(!add && index== -1) mail += "@gmail.com"; //abc@gmail.com

}
static void check(string& input, string field, string base) {
	if (field == "mail") {
		for (int i = 0; i < all_adm_members; i++) {
			administer adm = administers[i];
			if (adm.mail == input) {
				cout << "\tE-mail already exists! Try again: ";
				getline(cin, input);
				validateMail(input); //abc
				check(input, field, base);
				break;
			}
			for (int j = 0; j < adm.hiring; j++) {
				if (adm.eymployees[j].mail == input) {
					cout << "\tE-mail already exists! Try again: ";
					getline(cin, input);
					validateMail(input);
					check(input, field, base);
					break;
				}
			}
		}
	}
	else if (field == "pass") {
		if (base == "adm") {
			for (int i = 0; i < all_adm_members; i++) {
				administer adm = administers[i];
				if (adm.password == input) {
					cout << "\tPassword already taken! Try again: ";
					getline(cin, input);
					check(input, field, base);
					break;
				}
			}
		}
		else if (base == "eymp") {
			for (int i = 0; i < all_adm_members; i++) {
				administer adm = administers[i];
				for (int j = 0; j < adm.hiring; j++) {
					eymployee eymp = administers[i].eymployees[j];
					if (eymp.password == input) {
						cout << "\tPassword already taken! Try again: ";
						getline(cin, input);
						check(input, field, base);
						break;
					}
				}
			}
		}
	}
}
static int* findEmp(string input, string field) {
	int* arr = new int[2] {-1, -1};//0: admin, 1: eymp
	for (int i = 0; i < all_adm_members; i++) {
		for (int j = 0; j < administers[i].hiring; j++) {
			eymployee target = administers[i].eymployees[j];
			if (field == "id") {
				if (target.id == input) {
					arr[0] = i;
					arr[1] = j;
					return arr;
				}
			}
			else if (field == "mail") {
				if (target.mail == input) {
					arr[0] = i;
					arr[1] = j;
					return arr;
				}
			}
			else {
				if (target.password == input) {
					arr[0] = i;
					arr[1] = j;
					return arr;
				}
			}
		}
	}
	return arr;
}
static int findAdm(string input, string field) {
	int idx = -1;
	for (int i = 0; i < all_adm_members; i++) {
		administer target = administers[i];
		if (field == "id") {
			if (target.id == input) {
				idx = i;
				return idx;
			}
		}
		else if (field == "mail") {
			if (target.mail == input) {
				idx = i;
				return idx;

			}
		}
		else {
			if (target.password == input) {
				idx = i;
				return idx;

			}
		}
	}
	return idx;
}
static int findDpt(string input) {
	int idx = -1;
	for (int i = 0; i < 3; i++) {
		dpts* ptr = &adm_departments[i];
		if (ptr->department == input) {
			idx = i;
			return idx;
		}
	}
	return idx;
}
static void charFile(string name, int& val, string mode) {
	fstream file;
	if (mode == "read") {
		file.open(name, ios::in);
		if (file.fail()) val = 0;
		else file >> val;
	}
	else {
		file.open(name, ios::out);
		file << val << endl;
	}
	file.close();
}
static void dptInfo(string mode) {
	fstream file;
	if (mode == "write") {
		file.open("dptInfo", ios::out);
		for (int i = 0; i < 3; i++) {
			file << adm_departments[i].eymployees << " ";
			file << adm_departments[i].eymployers << " ";
			file << adm_departments[i].idStarts[0] << " ";
			file << adm_departments[i].idStarts[1] << " ";
			file << adm_departments[i].salary << endl;
		}
	}
	else {
		file.open("dptInfo", ios::in);
		for (int i = 0; i < 3; i++) {
			file >> adm_departments[i].eymployees;
			file >> adm_departments[i].eymployers;
			file >> adm_departments[i].idStarts[0];
			file >> adm_departments[i].idStarts[1];
			file >> adm_departments[i].salary;
		}
	}
	file.close();
}
static void eymWrite(string name, administer adm) {
	fstream file(name, ios::out);
	for (int i = 0; i < adm.hiring; i++) {
		eymployee eym = adm.eymployees[i];
		file << eym.name << "*";
		file << eym.id << " ";
		file << eym.mail << " ";
		file << eym.password << " ";
		file << eym.department << " ";
		file << eym.p << " ";
		file << eym.salary << endl;
	}
		file.close();
}

static void admWrite(string name, administer admin) {
	fstream file(name, ios::out);
	for (int i = 0; i < all_adm_members; i++) {
		administer admin = administers[i];
		file << admin.hiring << " ";
		file << admin.name << "*";
		file << admin.password << " ";
		file << admin.department << " ";
		file << admin.mail << " ";
		file << admin.id << " ";
		file << admin.empFile << endl;
	}
	file.close(); 
}
static void eymRead(string name, administer &adm) {
	fstream file(name, ios::in);
	for (int i = 0; i < adm.hiring; i++) {
		eymployee *eym = &adm.eymployees[i];
		getline(file, eym->name, '*');
		file >> eym->id;
		file >> eym->mail ;
		file >> eym->password ;
		file >> eym->department ;
		file >> eym->p;
		file >> eym->salary;
		eym->done= -1;
		eym->tasks= -1;
		eym->toDo = -1;
		eym->reg = 0;
		eym->work = 0;
	}
	file.close();
}
static void fileRead(string name) {
	fstream file(name, ios::in);
	for (int i = 0; i < all_adm_members; i++) {
		file >> administers[i].hiring;
		getline(file, administers[i].name, '*');
		file >> administers[i].password;
		file >> administers[i].department;
		file >> administers[i].mail;
		file >> administers[i].id;
		file >> administers[i].empFile;
		administers[i].tasks= -1;
		administers[i].complains= -1;
		administers[i].requests= 0;
		administers[i].reg = 0;
		if (administers[i].hiring != 0) eymRead(administers[i].empFile, administers[i]);
	}
	file.close();
}
static void load() {
	charFile("all_admins", all_adm_members, "read");
	if (all_adm_members!= 0) {
		charFile("all_emps", all_eymps, "read");
		dptInfo("read");
		fileRead("admin_files");// read admins and emps
		if (all_adm_members == 1) {
			cout << "\n\n\t\tData has been read from file due to project requirement.";
			cout << "\n\t\tData was entered manually by the program.\n";
			hold();
		}
	}
}
static string idAssign(string seed, string usage) {
	int currId, idx;
	string id, title;
	if (usage == "administer") { idx = 0; title = "A"; }
	else { idx = 1; title = "E"; }
	if (seed == "Computer") {
		id = "CS" + title + adm_departments[0].idStarts[idx];
		currId = stoi(adm_departments[0].idStarts[idx]);
		currId++;
		adm_departments[0].idStarts[idx] = to_string(currId);
		return id;
	}
	else if (seed == "Biology") {
		id = "BG" + title + adm_departments[1].idStarts[idx];
		currId = stoi(adm_departments[1].idStarts[idx]);
		currId++;
		adm_departments[1].idStarts[idx] = to_string(currId);
		return id;
	}
	else if (seed == "Management") {
		id = "MG" + title + adm_departments[2].idStarts[idx];
		currId = stoi(adm_departments[2].idStarts[idx]);
		currId++;
		adm_departments[2].idStarts[idx] = to_string(currId);
		return id;
	}
	dptInfo("write");

	return "0";
}
/*
int main() {
	int ch;
	load();
	do {
		cout << "\n\n\t\t-----WELCOME-----";
		cout << "\n\n\t1. Administration";
		cout << "\n\t2. Eymployee";
		cout << "\n\t3. Insight";
		cout << "\n\t4. End";
		cout << "\n\n\tEnter choice: ";
		cin >> ch;
		validateInput(ch, 3);
		system("CLS");
		switch (ch) {
		case 1:
			administration();
			break;
		case 2:
		{
			if (all_eymps == 0) {
				cout << "\n\tNo eymployee has been hired at the current stage!!";
				hold();
				break;
			}
			string pass;
			bool found = false;
			cout << "\n\tEnter password: ";
			cin.ignore();
			getline(cin, pass);
			int* idxes = findEmp(pass, "pass");
			if (*(idxes + 1) == -1) {
				cout << "\n\t\tSorry! We cannot find any eymployee. Try again! " << endl;
				hold();
				break;
			}
			cout << "\n\tLogged in! Welcome " << administers[idxes[0]].eymployees[idxes[1]].name << endl;
			hold();
			eymp_menu(idxes[0], idxes[1]);
			delete[] idxes;
			idxes = nullptr;
			break;
		}
		case 3:
		{
			for (int dpt = 0; dpt < 3; dpt++) {
				cout << "\n\n----------------------------------------------------------";
				cout << "\n\t\t" << adm_departments[dpt].department;
				cout << "\n Total Admins: " << adm_departments[dpt].eymployers;
				cout << "\t Total hiring: " << adm_departments[dpt].eymployees;
				cout << "\n----------------------------------------------------------";
				if (adm_departments[dpt].eymployers == 0) {
					cout << "\n\tNo Administers hired";
					continue;
				}
				for (int i = 0; i < all_adm_members; i++) { //itrate through all admins
					if (administers[i].department == adm_departments[dpt].department) {
						cout << "\n Admin: " << administers[i].name;
						cout << "\t ID: " << administers[i].id;
						cout << "\n--------------------------------------------";
						cout << "\n\tTotal Hiring: " << administers[i].hiring;
						cout << "\n--------------------------------------------";
						if (administers[i].hiring == 0) continue;
						for (int j = 0; j < administers[i].hiring; j++) {
							eymployee emp = administers[i].eymployees[j];
							cout << "\n\t" << j + 1 << ": NAME: " << emp.name << "\tID: " << emp.id;
						}
						cout << "\n--------------------------------------------";
					}
				}
			}
			cout << endl;
			hold();
			break;
		}
		case 4:
			return 0;
			break;
		}
	} while (1);

	return 0;
}

void administration()
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
			adm_register();
			break;
		case 2: //set salary
		{
			string dpt;
			dpts* ptr= 0; //points to desired dpt
			int dptNo = 0;
			cout << "\n\tCurrent Salary packages for eymployees are: \n";
			cout << "\n\tCOMPUTER: " << adm_departments[0].salary;
			cout << "\n\tBIOLOGY: " << adm_departments[1].salary;
			cout << "\n\tMANAGEMENT: " << adm_departments[2].salary;
			cout << "\n\n\tWhich department you would like to change: ";
			cin.ignore();
			getline(cin, dpt);
			dptNo = findDpt(dpt);
			system("CLS");
			if (dptNo != -1) {
				ptr = &adm_departments[dptNo];
				cout << "\n\tEnter new salary of " << ptr->department << " department: ";
				cin >> ptr->salary;
				cout << "\n\tSalary updated sucessfully!\n ";
				dptInfo("write");
				hold();
			}else {
				cout << "\n\tSorry! But we do have any department " << dpt << endl;
				hold();
			}
			break;
		}
		case 3: //log in eymployer
		{
			if (all_adm_members == 0) {
				cout << "\n\tNo eymployer has been registered at the current stage!!";
				hold();
				break;
			}
			string pass;
			bool found = false;
			cout << "\n\tEnter password: ";
			cin.ignore();
			getline(cin, pass);
			int index = findAdm(pass, "pass");
			if (index == -1) {
				cout << "\n\t\tSorry! We cannot find any registration. Try again! " << endl;
				hold();
				break;
			}
			cout << "\n\tLogged in! Welcome " << administers[index].name << endl;
			hold();
			adm_menu(index);
			break;
		}
		case 4:
			return;
			break;
		}
	} while (1);
}

void adm_register()
{
	string dpt;
	bool found = false;
	dpts* dp = 0;
	cout << "\n\tIn which department you want to register eymployer: ";
	cin.ignore();
	getline(cin, dpt);
	int dptNo = findDpt(dpt);
	if (dptNo != -1) found = true;
	if (found) {
		dp = &adm_departments[dptNo];
		if (dp->eymployers >= max_adm) {
			cout << "\n\tSorry capacity is full! Can not register more than "<< max_adm <<" eymployers in " << dpt<< endl;
			hold();
		}
		else {
			administer* adm = &administers[all_adm_members];
			cout << "\n\tPlease fill the required fields for eymployer: \n";
			adm->id = idAssign(dpt, "administer");
			cout << "\n\tID: "<< adm->id;
			adm->department = dpt;
			cout << "\n\tDEPARTMENT: "<< adm->department;
			cout << "\n\tNAME: "; getline(cin, adm->name);
			cout << "\tPASSWORD: "; getline(cin, adm->password);
			check(adm->password, "pass", "adm");
			cout << "\tMAIl: "; getline(cin, adm->mail);
			validateMail(adm->mail);// check syntax
			check(adm->mail, "mail", "adm");
			adm->hiring = 0; //has hired no one
			adm->complains = -1;
			adm->tasks = -1;
			adm->reg = 0;
			adm->requests = 0;
			adm->empFile = "empInfo" + adm->id;
			cout << "\n\tEymployer added sucessfully! Required information has been sent to \"" <<adm->name<< "\" via mail\n";
			(dp->eymployers)++;
			all_adm_members++; //for all departments administers
			charFile("all_admins", all_adm_members, "write");
			admWrite("admin_files", *adm);
			dptInfo("write");
			hold();
		}
	}
	else {
		cout << "\n\tSorry! But we do have any department \"" << dpt<< "\".\n";
		hold();
	}
}

void adm_menu(int adm)
{
	administer* user = &administers[adm]; 
	int dptNo = findDpt(user->department); //input can never be invalid
	dpts* department = &adm_departments[dptNo];
	int ch;
	do {
		cout << "\n\n\t\t-----DASHBOARD-----\n";
		cout << "\n\t1. View Profile";
		cout << "\n\t2. Hire Eymployees";
		cout << "\n\t3. Assign Tasks";
		cout << "\n\t4. Register";
		cout << "\n\t5. Requests";
		cout << "\n\t6. Eymployee List";
		cout << "\n\t7. Generate Payroll";
		cout << "\n\t8. Log Out";
		cout << "\n\n\tEnter choice: ";
		cin >> ch;
		validateInput(ch, 8);
		system("CLS");
		switch (ch) {
		case 1:
			cout << "\n--------------------------------------\n";
			cout << "\n\tNAME: " << user->name;
			cout << "\n\tDEPARTMENT: " << user->department;
			cout << "\n\tID: " << user->id;
			cout << "\n\tPASSWORD: " << user->password;
			cout << "\n\tMAIL: " << user->mail;
			cout << "\n\tHired Eymployees: " << user->hiring;
			cout << "\n\n--------------------------------------\n";
			hold();
			break;
		case 2: //Hire Eymployees
			system("CLS");
			if (department->eymployees >= max_eymp) {
				cout << "\n\tSorry capacity is full! Can not hire more than " << max_eymp << " eymployers in " << department->department << endl;
				hold();
				break;
			}
			hire_eymp(user, department);
			adm_reg(user, "hiring", NULL);
			break;
		case 3: { //assign task
			if (user->hiring == 0) {
				cout << "\n\tNo eymployee has been hired yet!\n";
				hold();
				break;
			}
			string input;
			cout << "\n\tYou can only assign task to those eymployee whom you have hired!\n";
			cout << "\n\tEnter ID or MAIL of eymployee: "; 
			cin.ignore();
			getline(cin, input);
			int *idxes = findEmp(input, "id");
			if (idxes[1] == -1) {
				validateMail(input);
				idxes = findEmp(input, "mail");
				if (idxes[1] == -1 ) {
					cout << "\n\tCannot find any eymployer with provided credentials!!";
					hold();
					break;
				}
			}
			if (administers[*idxes].id != user->id) {
				cout << "\n\tSorry you have made no hiring of this ID";
				hold();
				break;
			}
			assign_task(&user->eymployees[idxes[1]]);
			adm_reg(user, "task", &user->eymployees[idxes[1]]);
			delete[] idxes;
			idxes = nullptr;
			break;
		}
		case 4: //registter
			cout << "\n\tYour activities are as follow:\n\n";
			if (user->tasks == -1) {
				cout << "\n\tNo tasks to note!";
				hold();
				break;
			}
			for (int i = 0; i <= user->tasks; i++) {
				cout << "\t" << i + 1 << ": " << user->reg[i] << endl;
			}
			hold();
			break;
		case 5: //request
		{
			int ch;
			cout << "\n\tYour current requests are following: ";
			for (int i = 0; i <= user->complains; i++) {
				cout << "\n--------------------------------------\n\n";
				cout << "\t" << i + 1 << ": " << "COMPLAIN: " << user->requests[i].problem;
				cout << "\n\t  ID: " << user->requests[i].id << setw(3) << "\t  NAME: " << user->requests[i].name << setw(3) << "\t  MAIL: " << user->requests[i].mail;
				int* idxes = findEmp(user->requests[i].id, "id");
				if (user->id != administers[*idxes].id) cout << "\t(Not your eymployee!!)";
				cout << "\n\n--------------------------------------\n";
				delete[] idxes;
			}
			cout << "Total Complains: " << user->complains + 1 << endl;
			cout << "\n\tPress 0 to exit or complain No. to delete complain: ";
			cin >> ch;
			if (ch > 0 && ch <= user->complains+1) {
				update_arr(user->requests, user->complains, ch);
				user->complains--;
				cout << "\n\tDeleted Sucessfully";
				hold();
			}
			system("CLS");
			break;
		}
		case 6://eymployee list
			cout << "\n\tYou hired no employees!\n";
			cout << "\n\tYou Hiring is:\n";
			for (int i = 0; i < user->hiring; i++) {
				cout << "\n\t" << i + 1 << ": " << "Name: " << user->eymployees[i].name << "\tID: " << user->eymployees[i].id << "\tMAIL: " << user->eymployees[i].mail;
			}
			cout << endl;
			hold();
		break;
		case 7: //generate payroll
		{
			string input;
			cout << "\n\tEnter ID or MAIL of eymployee: ";
			cin.ignore();
			getline(cin, input);
			int *idxes = findEmp(input, "id");
			if (idxes[1] == -1) {
				validateMail(input);
				idxes = findEmp(input, "mail");
				if (idxes[1] == -1) {
					cout << "\n\tCannot find any eymployer with provided credentials!!";
					hold();
					break;
				}
			}
			if (administers[*idxes].id != user->id) {
				cout << "\n\tSorry you have made no hiring of this ID";
				hold();
				break;
			}
			gen_sal(user,idxes[1]);
			adm_reg(user, "salary", &user->eymployees[idxes[1]]);
			delete[]idxes;
			idxes = nullptr;
			break;
		}
		case 8:
			return;
			break;
		}
	} while (1);
}
void hire_eymp(administer* user, dpts* department) {
	cout << "\n\tYou can hire eymployee only in \"" << user->department << "\" department";
	cout << "\n\tFill the credentials of eymployee: " <<endl;
	user->eymployees[user->hiring].id = idAssign(department->department, "eymployee");
	cout << "\n\tID: " << user->eymployees[user->hiring].id;
	user->eymployees[user->hiring].department = department->department;
	cout << "\n\tDEPARTMENT: " << user->eymployees[user->hiring].department;
	cout << "\n\tDEPARTMENT SALARY: " << department->salary;
	cin.ignore();
	cout << "\n\tNAME: "; getline(cin, user->eymployees[user->hiring].name);
	cout << "\tPASSWORD: "; getline(cin, user->eymployees[user->hiring].password);
	check(user->eymployees[user->hiring].password,"pass", "eymp");
	cout << "\tMAIl: "; getline(cin, user->eymployees[user->hiring].mail);
	validateMail(user->eymployees[user->hiring].mail);
	check(user->eymployees[user->hiring].mail, "mail", "eymp");
	user->eymployees[user->hiring].reg = 0;
	user->eymployees[user->hiring].work = 0;
	user->eymployees[user->hiring].toDos = 0;
	user->eymployees[user->hiring].toDo = -1;
	user->eymployees[user->hiring].tasks = -1; // no assign tasks
	user->eymployees[user->hiring].done = -1; // no register tasks
	user->eymployees[user->hiring].p = 0; 
	user->eymployees[user->hiring].salary = department->salary;
	cout << "\n\tEymployee has been hired sucessfully! Credentials has been sent to \"" << user->eymployees[user->hiring].name << "\" via mail\n";
	user->hiring++;
	department->eymployees++;
	all_eymps++;
	charFile("all_emps", all_eymps, "write");
	eymWrite(user->empFile, *user);
	admWrite("admin_files", *user);
	dptInfo("write");
	hold();
}
void assign_task(eymployee* eymp)
{ 
	if (eymp->tasks == -1) { 
		eymp->tasks++; //0
		eymp->work = new workLoad[eymp->tasks+1];//1
	}
	else { // copy 1
		workLoad* copy = new workLoad[eymp->tasks+1];//2
		copy = eymp->work;
		eymp->work = new workLoad[eymp->tasks+2];//2
		for (int i = 0; i <= eymp->tasks; i++) {
			eymp->work[i].task = copy[i].task;
			eymp->work[i].dueDate = copy[i].dueDate;
			eymp->work[i].instruction = copy[i].instruction;
		}
		eymp->tasks++;//1
		delete[] copy;
		copy = nullptr;

	} 
	cout << "\n\n\tPlease Enter task info: \n";
	cout << "\n\t TASK TITLE: ";
	getline(cin, eymp->work[eymp->tasks].task);
	cout << "\t DUE-DATE: ";
	cin >> eymp->work[eymp->tasks].dueDate; cin.ignore();
	cout << "\t INSTRUCTION: ";
	getline(cin, eymp->work[eymp->tasks].instruction);
	cout << "\n\n\tTask has been Assigned to \""<<eymp->name<<"\" Sucessfully!";
	hold();

}
void adm_reg(administer* user, string base, eymployee* eymp)
{
	if (user->tasks == -1) {
		user->tasks++; //0
		user->reg = new string[user->tasks + 1];//1
	}
	else { // copy 1
		string* copy = new string[user->tasks + 1];//2
		copy = user->reg;
		user->reg = new string[user->tasks + 2];//2
		for (int i = 0; i <= user->tasks; i++) {
			user->reg[i] = copy[i];
		}
		user->tasks++;//1
		delete[] copy;
		copy = nullptr;

	}
	if (base == "hiring") {
		user->reg[user->tasks] = "Hired \""+user->eymployees[user->hiring - 1].name+ "\"\t ID: " + user->eymployees[user->hiring - 1].id;
	}else if (base == "task") {
		user->reg[user->tasks] = "Assign task to \"" + eymp->name + "\"\t ID: " + eymp->id;
	}
	else if (base == "salary") {
		user->reg[user->tasks] = "Generated Payroll of \"" + eymp->name + "\"\t ID: " + eymp->id;
	}
}

void gen_sal(administer* user, int idx)
{
	int dptNo = findDpt(user->department);
	dpts dpt = adm_departments[dptNo];
	eymployee* eymp = &user->eymployees[idx];
	cout << "\n\tName: " << eymp->name;
	cout << "\n\tDepartment Salary: " << dpt.salary;
	cout << "\n\tAssigned Salary: " << eymp->salary;
	cout << "\n\tMonthly Attendance: " << eymp->p;
	cout << "\n\tCurrent Salary: " << (float(eymp->p) / 30) * eymp->salary;
	cout << "\n\n\tYour action will change \"" << eymp->name << "\'\" assigned salary.";
	cout << "\n\tYou are to justify yourself for this act e.g deduction, bonus etc!!\n";
	hold();
	cout << "\n\tEnter new Salary: ";
	cin >> eymp->salary;
	eymWrite(user->empFile, *user);
	cout << "\n\tUpdated Sucessfully\n";
	hold();
}

void update_arr(request* &array, int size, int dlt)
{
	request* temp = new request[size];
	int idx = 0;
	for (int i = 0; i <= size; i++) { //0
		if (i != dlt - 1) { //0!= 1
			temp[idx] = array[i];
			idx++;
		}
	}
	delete[] array;
	array = temp;
	delete[] temp;
	temp = nullptr;
}

//eymployee--------------------------------------------------------------------------

void eymp_menu(int adm_idx, int eymp_idx)
{
	administer* admin = &administers[adm_idx];
	eymployee* user = &admin->eymployees[eymp_idx];
	bool allow = true; //to mark attendence
	int ch;
	do {
		cout << "\n\n\t\t-----DASHBOARD-----\n";
		cout << "\n\t1. View Profile";
		cout << "\n\t2. TO-DO List";
		cout << "\n\t3. Work Load";
		cout << "\n\t4. Register Requets";
		cout << "\n\t5. Register";
		cout << "\n\t6. Mark Attendance";
		cout << "\n\t7. Salary Information";
		cout << "\n\t8. Log Out";
		cout << "\n\n\tEnter choice: ";
		cin >> ch;
		validateInput(ch, 8);
		system("CLS");
		switch (ch) {
		case 1:
			cout << "\n--------------------------------------\n";
			cout << "\n\tNAME: " << user->name;
			cout << "\n\tDEPARTMENT: " << user->department;
			cout << "\n\tID: " << user->id;
			cout << "\n\tPASSWORD: " << user->password;
			cout << "\n\tMAIL: " << user->mail;
			cout << "\n\tASSIGN TASKS: " << user->tasks+1;
			cout << "\n\tPRESENt: " << user->p;
			cout << "\n\tEYMPLOYER: " << admin->name;
			cout << "\n\tEYMPLOYER MAIL: " << admin->mail;
			cout << "\n\tEYMPLOYER ID: " << admin->id;
			cout << "\n\n--------------------------------------\n";
			hold();
			break;
		case 2: {//to do list
			int ch;
			cout << "\n\n---------------TO DO\'s-----------------------\n";
			if (user->toDo == -1) cout << "\n\tNo Tasks added!\n";
			else {
				for (int i = 0; i <= user->toDo; i++) {
					cout << "\n\t" << i + 1 << ": " << user->toDos[i] << endl;
				}
			}
			cout << "\n\n--------------------------------------\n";
			cout << "Total Tasks: " << user->toDo+1;
			cout << "\n\n\tPress \'-1\' to exit, \'0\' to add Task, and Task no to delete: ";
			cin >> ch;
			if (ch != -1) {
				system("CLS");
				if (ch == 0) {
					toDoList(user);
					cout << "\n\tAdded Sucessfully!\n";
				}
				else if (ch <= user->toDo + 1) {
					toDoDlt(user->toDos, user->toDo, ch - 1);
					user->toDo--;
					cout << "\n\tDeleted Sucessfully!\n";
				}
				else cout << "\n\tTask not found!";
				hold();
			}
			else system("CLS");
			break;
		}
		case 3://work load
			cout << "\n\tYour current work load is following: ";
			cout << "\n--------------------------------------\n\n";
			cout << "\tTASK" << setw(6) << " | " <<setw(6) << "DUE-DATE" << setw(6) << " | " << setw(6) << "DESCRIPTION\n\n";
			for (int i = 0; i <= user->tasks; i++) {
				cout << "\t" << i+1 << ": " << user->work[i].task << setw(6) << " | " << setw(6) << user->work[i].dueDate << setw(6) << " | " << setw(6) << user->work[i].instruction << endl;
			}
			cout << "\n\n--------------------------------------\n";
			cout << "\tTotal Tasks: "<< user->tasks+1;
			hold();
			break;
		case 4: {//register request
			string input;
			cout << "\n\tPlease enter eymployer's ID or MAIL: ";
			cin.ignore();
			getline(cin, input);
			int idx = findAdm(input, "id");
			if (idx == -1) {
				validateMail(input);
				idx = findAdm(input, "mail");
				if (idx == -1) {
					cout << "\n\tCannot find any eymployer with provided credentials!!";
					hold();
					break;
				}
			}
			reg_req(&administers[idx], *user);
			eymp_reg(user, "request", &administers[idx]);
			break;
		}
		case 5: //register
			cout << "\n\tYour activities are as follow:\n\n";
			if (user->done == -1) { cout << "\n\tNo activities to note!!"; hold(); }

			for (int i = 0; i <= user->done; i++) {
				cout << "\t" << i + 1 << ": " << user->reg[i] << endl;
			}
			hold();
			break;
		case 6://attendence
			if (allow) {
				user->attendence[user->p] = 'P';
				user->p++;
				cout << "\n\tYour attendance has been marked. Remember that Your attendance affects your payroll calculations\n";
				allow = false;
				cout << "\n----ATTENDANCE SHEET----\n";
				cout << "\tDAY\t ATTENDANCE\n";
				cout << "---------------------\n";
				for (int i = 0; i < user->p; i++) {
					cout << '\t' << i + 1 << '\t' << user->attendence[i] << endl;
				}
				eymp_reg(user, "attend", NULL);
			}
			else
				cout << "\n\tYou have already marked the attendance!!\n";
			hold();
			break;
		case 7: //salary detail
		{
			int dptNo = findDpt(user->department); 
			dpts dpt = adm_departments[dptNo];
			cout << "\n\t\t----SALARY DETAILS----\n";
			cout << "\n\tDepartment Salary: " << dpt.salary;
			cout << "\n\tAssigned Salary: " << user->salary;
			cout << "\n\tMonthly Attendance: " << user->p;
			cout << "\n\tCurrent Salary: " << (float(user->p) / 30) * user->salary;
			cout << "\n\n-----------------------------------------";
			cout << "\n\n\tYour Current Salary is calculated bases on your preformance.\n\tIf you have any quiries related to your Assigned salary,\n\tYou can register request to your eymployer\n";
			hold();
			break;
		}
		case 8:
			return;
			break;
		}
	} while (1);
}

void reg_req(administer* admin, eymployee user)
{
	if (admin->complains == -1) {
		admin->complains++; //0
		admin->requests = new request[admin->complains+1];//1
	}
	else { // copy 1
		request* copy = new request[admin->complains + 1];//2
		copy = admin->requests;
		admin->requests = new request[admin->complains + 2];//2
		for (int i = 0; i <= admin->complains; i++) {
			admin->requests[i].name = copy[i].name;
			admin->requests[i].id = copy[i].id;
			admin->requests[i].mail = copy[i].mail;
			admin->requests[i].problem = copy[i].problem;
		}
		admin->complains++;//1
		delete[] copy;
		copy = nullptr;
	}
	string complain;
	cout << "\n\tFill the following form: \n";
	cout << "\n\t NAME: " << user.name;
	admin->requests[admin->complains].name = user.name;
	cout << "\n\t ID: " << user.id;
	admin->requests[admin->complains].id = user.id;
	cout << "\n\t MAIL: " << user.mail;
	admin->requests[admin->complains].mail = user.mail;
	cout << "\n\t COMPLAIN: ";
	getline(cin, complain);
	admin->requests[admin->complains].problem = complain;
	cout << "\n\tComplain has been registered to \"" << admin->name << "\" Sucessfully!";
	hold();
}

void eymp_reg(eymployee* user, string base, administer* admin)
{
	if (user->done == -1) {
		user->done++; //0
		user->reg = new string[user->done + 1];//1
	}
	else { // copy 1
		string* copy = new string[user->done + 1];//2
		copy = user->reg;
		user->reg = new string[user->done + 2];//2
		for (int i = 0; i <= user->done; i++) {
			user->reg[i] = copy[i];
		}
		user->done++;//1
		delete[] copy;
		copy = nullptr;
	}
	if (base == "request") {
		user->reg[user->done] = "Request registered to \"" + admin->name + "\"\t MAIL: " + admin->mail;
	}
	else if (base == "attend") {
		user->reg[user->done] = "Marked Attendance";
	}	 
}

void toDoList(eymployee* user)
{
	if (user->toDo == -1) {
		user->toDo++;
		user->toDos = new string[user->toDo + 1];
	}
	else {
		string* temp = new string[user->toDo + 1];
		temp = user->toDos;
		user->toDos = new string[user->toDo + 2];
		for (int i = 0; i <= user->toDo; i++) {
			user->toDos[i] = temp[i];
		}
		user->toDo++;
		delete[] temp;
		temp = nullptr;
	}
	cout << "\n\tEnter Task: ";
	cin.ignore();
	getline(cin, user->toDos[user->toDo]);
}

void toDoDlt(string* &list, int size, int dlt)
{
	string* temp = new string[size];
	int idx = 0;
	for (int i = 0; i <= size; i++) { //0
		if (i != dlt) { //0!= 1
			temp[idx] = list[i];
			idx++;
		}
	}
	delete[] list;
	list = temp;
	delete[] temp;
	temp = nullptr;
}
/*
*/
