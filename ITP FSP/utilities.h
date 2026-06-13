#pragma once

#include <string>
#include "Mail.h"

using namespace std;

class Company;
class DepartmentInfo;

// Prototypes for utility functions. Implementations are in utilities.cpp
Mail composeMail(string sender, string receiver);
void validateInput(int& ch, int range);
void hold(string msg);
void hold();
void hold(int stopper);
int getDptNo();
void addAt(string &mail);
bool validMail(string mail);
void displayDpt(DepartmentInfo& dpt);
