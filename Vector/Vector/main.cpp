#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <ctime>
#include "Vector.h"
using namespace std;
using std::vector;


int main()
{
	//float 값을 가지는 Vector를 생성한다.
	//템플릿 프로그래밍을 이용하여 다양한 Vector 자료형 값을 지원하는 클래스를 만든다.

	// Vector끼리의 사칙연산, Vector의 기저벡터값을 구하는 기능을 추가한다.

	Vector<float> fVec0{10.f,5.f};

	Vector<int> iVec0(fVec0);


	iVec0 = iVec0 - fVec0;

	fVec0.printValue();
	iVec0.printValue();


	// Vector 를 vector 컨테이너에 담아서 iterator, lamda, functor 등 여러가지를 이용해서 연습해보기

	
}