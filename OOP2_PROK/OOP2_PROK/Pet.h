#pragma once
#include <iostream>
#include <string> // <cstring> or <string.h> -> string�Լ� ����

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

	// age(�ð��� ���� ���ϴ� ��) -> �������(���ȭ ��ų�� �ִ� ��) idea
	int		 m_age;
	

};

