#include "Student.h"
#include <string.h>
#include <iostream>
#include<iomanip>
using namespace std;
Student::Student()
{
	strcpy_s(id, "");
	strcpy_s(name, "");
	result = 7;
}

Student::Student(char* _id, char* _name, float _result)
{
	strcpy_s(this->id, 10, _id);
	strcpy_s(this->name, 50, _name);
	this->result = _result;
}

Student::~Student()
{
}
//=================== NHAP THONG TIN SINH VIEN =======================
void Student::scan() {
	cout << "-> Thong tin sinh vien:" << endl;
	cout << "\tMSSV: ";
	cin.ignore();
	cin.getline(id, 10);
	cout << "\tTen: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\tDiem: ";
	cin.ignore();
	cin >> result;
}

void Student::print()
{
	cout << "\tMSSV\t:" << this->id << endl;
	cout << "\tTen\t:" << this->name << endl;
	cout << "\tDiem\t:" << setprecision(2) << fixed << this->result << endl;
}
Student Student::operator=(const Student& S)
{
	
	strcpy_s(this->id, S.id);
	strcpy_s(this->name, S.name);
	this->result = S.result;
	return *this;
}
