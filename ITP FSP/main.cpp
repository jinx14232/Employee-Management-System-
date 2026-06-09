#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include"Company.h"
#include"utilities.h"
#include"administration.h"
#include"employment.h"

int main(void) {
	Company company;

	int ch;
	do {
		cout << "\n\n\t\t-----WELCOME-----";
		cout << "\n\n\t1. Administration";
		cout << "\n\t2. Employee";
		cout << "\n\t3. Insight";
		cout << "\n\t4. End";
		cout << "\n\n\tEnter choice: ";
		cin >> ch;
		validateInput(ch, 4);
		system("CLS");
		switch (ch) {
		case 1:
			administration(company);
			break;
		case 2:
		{
			if (Company::allEmps == 0) {
				cout << "\n\tNo employees at the moment!";
				hold("Press any key to continue: ");
				break;
			}
			employment(company);
			
			break;
		}
		case 3:
		{
			company.insight();
			break;
		}
		case 4:
			return 0;
			break;
		}
	} while (1);
}


