#pragma once
#include<iostream>
#include<string>
using namespace std;

class WorkLoad {
private:
	string task;
	int dueDate;
	string instruction;
public:
	WorkLoad() {
		task = "";
		dueDate = 0;
		instruction = "";
	}
	WorkLoad(string task, int dueDate, string instruction) {
		this->task = task;
		this->dueDate = dueDate;
		this->instruction = instruction;
	}
	string getTask() const { return task; }
	int getDueDate() const { return dueDate; }
	string getInstruction() const { return instruction; }

};


