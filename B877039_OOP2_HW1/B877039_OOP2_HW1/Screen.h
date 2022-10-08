#pragma once
class Screen
{
private:
	// Screen Scale
	int m_nCols;
	int m_nRows;

	char* m_map;

public:
	void render(const char* map);

private:


public:
	Screen(int Rows, int Cols);
	~Screen();
};

