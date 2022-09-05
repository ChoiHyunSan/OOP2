#pragma once
#include <iostream>
#include <string> // <cstring> or <string.h> -> string함수 관련

using namespace std;

class Pet
{
public:
	Pet(string, int);
	virtual ~Pet();

	virtual void eat();

	/*void setAge(const int age);*/
	int getAge();

	/*void setName(const string name);*/
	string getName();

protected:
	string	 m_name;

	// age(시간에 따라 변하는 값) -> 생년월일(상수화 시킬수 있는 값) idea
	int		 m_age;
	

};

