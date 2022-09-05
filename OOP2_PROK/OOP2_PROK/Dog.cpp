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
	cout << "개가 먹습니다" << endl;
}

void Dog::bark()
{
	cout << m_age << "살짜리 강아지 " << m_name << "가 짖습니다" << endl;
}