#include "Dog.h"
#include <iostream>

using namespace std;

Dog::Dog()
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