#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;
using std::vector;

class Student;

class Student
{
	string name;
	int age;

public:
	string getName() const { return name; }
	int getAge()const { return age; }

public:
	Student(const string& name, int age) : name(name), age(age) {}

	friend ostream& operator<<(ostream& os, const Student& s);


	friend bool isMultipleOfFive(const Student& item);
};

ostream& operator<<(ostream& os, const Student& s)
{
	cout << "name " << s.name << ", age = " << s.age;
	return os;
}


template<typename T>
bool isMultipleOfFive(const T& item)
{
	return item % 5 == 0;
}

template<>
bool isMultipleOfFive(const Student& item)
{
	return item.age % 5 == 0;
}



template<typename T>
void print(const T* data, int size)
{
	for (int i = 0; i < size; i++)
		cout << data[i] << endl;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& container)
{
	for (const auto& item : container)
	{
		cout << item << endl;
	}
	return os;
}

int main()
{
	vector<Student> ints;
	ints.push_back(Student("lee", 20));
	ints.push_back(Student("kim", 30));
	ints.push_back(Student("park", 40));

	cout << ints;

	auto pos = ints.begin();

	//print(ints.data(), ints.size());

	while ((pos = find_if(pos, ints.end(), isMultipleOfFive<Student*>)) != ints.end())
	{
		
	}

	return 0;
}



