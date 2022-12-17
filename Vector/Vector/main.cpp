#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <ctime>
#include "Vector.h"
using namespace std;
using std::vector;

class Three
{
public:
	bool operator()(const unique_ptr<Vector<float>>& vec)
	{
		return vec->X() == 3.0f;
	}
};

bool isThree(const unique_ptr<Vector<float>>& vec)
{
	return vec->X() == 3.0f;
}

int main()
{
	//float ���� ������ Vector�� �����Ѵ�.
	//���ø� ���α׷����� �̿��Ͽ� �پ��� Vector �ڷ��� ���� �����ϴ� Ŭ������ �����.

	// Vector������ ��Ģ����, Vector�� �������Ͱ��� ���ϴ� ����� �߰��Ѵ�.

	Vector<float> fVec0{10.f,5.f};

	Vector<int> iVec0(fVec0);
	cout << fixed;
	cout.precision(3);

	iVec0 = iVec0 - fVec0;
	fVec0 = fVec0 - iVec0;

	iVec0 = 3 * fVec0;

	//iVec0.printValue();
	//fVec0.printValue();

	// Vector �� vector �����̳ʿ� ��Ƽ� iterator, lamda, functor �� ���������� �̿��ؼ� �����غ���
	
	vector<unique_ptr<Vector<float>>> vectors;

	vectors.push_back(move(make_unique<Vector<float>>(0.f,1.f)));
	vectors.push_back(move(make_unique<Vector<float>>(3.f,2.f)));
	vectors.push_back(move(make_unique<Vector<float>>(0.f,2.f)));
	vectors.push_back(move(make_unique<Vector<float>>(3.f,3.f)));
	vectors.push_back(move(make_unique<Vector<float>>(0.f,4.f)));
	vectors.push_back(move(make_unique<Vector<float>>(3.f,7.f)));
	vectors.push_back(move(make_unique<Vector<float>>(3.f,5.f)));

	for (const auto& vec : vectors)
	{
		vec->printValue();
	}

	cout << "////////////////////////////////" << endl;

	// unique_ptr�̱� ������ �ش� vector iterator�� ���� ���� ����� �������� �ؼ� ������ �߻�
	// ex) auto vector -> const auto& vector�� �����Ͽ� ���� �ذ�

	// using Lamda Function
	vectors.erase(remove_if(vectors.begin(), vectors.end(),
		[&](const auto& vector) {
		return vector->X() == 3.f;
	}), vectors.end());


	// using Functor
	//vectors.erase(remove_if(vectors.begin(), vectors.end(),
	//	Three()), vectors.end());

	// using Function
	//vectors.erase(remove_if(vectors.begin(), vectors.end(),
	//	isThree), vectors.end());

	vectors.resize(vectors.size());

	for (const auto& vec : vectors)
	{
		vec->printValue();
	}

	
}