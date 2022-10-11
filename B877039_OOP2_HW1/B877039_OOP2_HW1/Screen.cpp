#include "Screen.h"
#include <string.h>
#include <iostream>
#include <iomanip>
#include "Utils.h"
#pragma warning(disable: 4996)

using namespace std;

void Screen::render(const char* map)
{
	m_map = new char[m_nCols * m_nRows+1];
	strcpy(m_map, map);

	Borland::GotoXY(0, 0);
	cout << "   ";
	for (int i = 0; i < m_nCols; i++)
		cout << i + 1 << " ";

	cout << endl;
	for (int i = 0; i < m_nCols; ++i)
	{
		cout << setw(2) << setfill('0') << i + 1<< " ";
		for (int j = 0; j < m_nRows; ++j)
		{
			cout << m_map[i * m_nCols + j] << " ";
		}
		cout << endl;
	}
}


Screen::Screen(int Rows, int Cols)
	: m_nRows(Rows), m_nCols(Cols) , m_map(nullptr)
{

}

Screen::~Screen()
{
	delete[] m_map;
}
