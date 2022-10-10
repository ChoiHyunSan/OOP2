#include "Screen.h"
#include <string.h>
#include <iostream>
#include "Utils.h"
#pragma warning(disable: 4996)

using namespace std;

void Screen::render(const char* map)
{
	m_map = new char[m_nCols * m_nRows];
	strcpy(m_map, map);

	Borland::GotoXY(0, 0);
	printf("%s", m_map);
}


Screen::Screen(int Rows, int Cols)
	: m_nRows(Rows), m_nCols(Cols) , m_map(nullptr)
{

}

Screen::~Screen()
{
	delete[] m_map;
}
