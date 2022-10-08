#include "Game.h"
#include "Screen.h"
#include <vector>
#include "Utils.h"

using std::vector;

Game::Game()
	:
	m_score(0),
	m_nCols(COLS),
	m_nRows(ROWS),
	m_screen(nullptr),
	m_mineNum(15),
	m_randMineIndex(nullptr)
{
	init();
}

Game::~Game()
{
	if (m_screen != nullptr)
		delete m_screen;

	if (m_mineMap != nullptr)
		delete[] m_mineMap;

	if (m_windowMap != nullptr)
		delete[] m_windowMap;

	if (m_randMineIndex != nullptr)
		delete[] m_randMineIndex;
}

void Game::init()
{

	// Create Screen
	m_screen = new Screen(m_nRows, m_nCols);

	// Init borland
	Borland::Initialize();

	// Init Map
	initMap();

}

void Game::render()
{
	m_screen->render(m_mineMap);
}

void Game::update()
{
	
}

void Game::input()
{

}

void Game::play()
{
	//while (1)
	{
		input();
		update();
		render();
	}
}

// 랜덤하게 지뢰를 세팅을 하는 함수에 대한 수정이 필요함
void Game::setMine(char* mineMap, const int size)
{
	int count = 0;
	while (count < m_mineNum)
	{
		m_randMineIndex[count] = rand() % (size-1);

		for (int i = 0; i < count; i++)
		{
			if (m_randMineIndex[count] == m_randMineIndex[i])
			{
				count--;
				break;
			}
		}	
		if (m_randMineIndex[count] % m_nCols == m_nRows)
		{
			continue;
		}
		count++;
	}
	for (int i = 0; i < m_mineNum; ++i)
	{
		m_mineMap[m_randMineIndex[i]] = 'X';
	}
}

void Game::initMap()
{
	// Init Map
	m_mineMap = new char[m_nCols * m_nRows];
	m_windowMap = new char[m_nCols * m_nRows];

	// Set NULL Char
	m_mineMap[m_nCols * m_nRows - 1] = '\0';
	m_windowMap[m_nCols * m_nRows - 1] = '\0';

	// init Mine Index
	m_randMineIndex = new char[m_mineNum];

	// Set mineMap
	memset(m_mineMap, '0', m_nCols * m_nRows - 1);
	for (int i = 0; i < m_nRows - 1; ++i)
		m_mineMap[i * m_nCols + m_nRows] = '\n';
	setMine(m_mineMap, m_nCols * m_nRows);

	// Set windowMap
	memset(m_windowMap, '0', m_nCols * m_nRows - 1);
	for (int i = 0; i < m_nRows - 1; ++i)
		m_windowMap[i * m_nCols + m_nRows] = '\n';
}
