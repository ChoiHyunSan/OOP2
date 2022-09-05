#pragma once
#include <iostream>
#include <cstring>
#include <string.h>

using namespace std;

class Pet
{
public:
	Pet();
	virtual ~Pet();

	virtual void eat();

	void setAge(const int age);
	int getAge();

	void setName(const string name);
	string getName();

protected:
	string	 m_name;
	int		 m_age;
	

};

