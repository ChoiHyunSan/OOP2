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
	//float ���� ������ Vector�� �����Ѵ�.
	//���ø� ���α׷����� �̿��Ͽ� �پ��� Vector �ڷ��� ���� �����ϴ� Ŭ������ �����.

	// Vector������ ��Ģ����, Vector�� �������Ͱ��� ���ϴ� ����� �߰��Ѵ�.

	Vector<float> fVec0{10.f,5.f};

	Vector<int> iVec0(fVec0);


	iVec0 = iVec0 - fVec0;

	fVec0.printValue();
	iVec0.printValue();


	// Vector �� vector �����̳ʿ� ��Ƽ� iterator, lamda, functor �� ���������� �̿��ؼ� �����غ���

	
}