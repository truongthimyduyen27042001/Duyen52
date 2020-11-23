#pragma once
#include<string.h>
class Student
{
//protected:
public:
	char id[10];
	char name[50];
	float result;
public:
	Student();
	Student(char *id, char *name, float result);
	~Student();
	void scan();
	void print();
	Student operator=(const Student&);
};

