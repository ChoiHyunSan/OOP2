#pragma once
#include "Utils.h"
#include <iostream>

using namespace std;

class Screen
{
	char*	m_lines;
	int		m_nRows;
	int		m_nCols;

private:
	int pos2offset(int x, int y, int n_cols)
	{
		return y * n_cols + x;
	}

public:
	Screen(int n_rows, int n_cols)
		: m_nRows(n_rows), m_nCols(n_cols),
		m_lines(new char[m_nRows * m_nCols + 1])
	{
		// init borland
		Borland::Initialize();

		// init screen
		memset(m_lines, '0', m_nRows * m_nCols);
		for (int i = 0; i < m_nRows - 1; ++i)
			m_lines[i * m_nCols + m_nRows] = '\n';
		m_lines[m_nRows * m_nCols - 1] = '\0';

	}

	virtual ~Screen() {  }

	void clear()
	{
		memset(m_lines, '0', m_nRows * m_nCols);
		for (int i = 0; i < m_nRows - 1; ++i)
			m_lines[i * m_nCols + m_nRows] = '\n';
		m_lines[m_nRows * m_nCols - 1] = '\0';
	}

	void draw(Position playerPos, char playerShape)
	{
		int offset = pos2offset(playerPos.x, playerPos.y, m_nCols);
		m_lines[offset] = playerShape;
	}

	void render()
	{
		Borland::GotoXY(0, 0);
		printf("%s", m_lines);
	}


};

