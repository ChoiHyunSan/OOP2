#include "Pet.h"

using namespace std;

Pet::Pet() : m_age(0)
{

}

Pet::~Pet()
{

}

void Pet::eat()
{
	cout << "¹äÀ» ¸Ô½À´Ï´Ù" << endl;
}

void Pet::setAge(const int age)
{
	m_age = age;
}

int Pet::getAge()
{
	return m_age;
}

void Pet::setName(const string name)
{
	m_name = name;
}

string Pet::getName()
{
	return m_name;
}
