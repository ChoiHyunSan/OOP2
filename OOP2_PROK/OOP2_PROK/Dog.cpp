#include "Dog.h"
#include <iostream>

using namespace std;

Dog::Dog(string name, int age) : Pet(name, age)
{
	
}

Dog::~Dog()
{

}

void Dog::eat()
{
	cout << "���� �Խ��ϴ�" << endl;
}

void Dog::bark()
{
	cout << m_age << "��¥�� ������ " << m_name << "�� ¢���ϴ�" << endl;
}