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
	//float 값을 가지는 Vector를 생성한다.
	//템플릿 프로그래밍을 이용하여 다양한 Vector 자료형 값을 지원하는 클래스를 만든다.

	// Vector끼리의 사칙연산, Vector의 기저벡터값을 구하는 기능을 추가한다.

	Vector<float> fVec0{10.f,5.f};

	Vector<int> iVec0(fVec0);
	cout << fixed;
	cout.precision(3);

	iVec0 = iVec0 - fVec0;
	fVec0 = fVec0 - iVec0;

	iVec0 = 3 * fVec0;

	//iVec0.printValue();
	//fVec0.printValue();

	// Vector 를 vector 컨테이너에 담아서 iterator, lamda, functor 등 여러가지를 이용해서 연습해보기
	
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

	// unique_ptr이기 때문에 해당 vector iterator에 대한 값을 복사로 가져오려 해서 오류가 발생
	// ex) auto vector -> const auto& vector로 수정하여 오류 해결

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