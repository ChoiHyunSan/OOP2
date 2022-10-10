#include "Game.h"
#include "Screen.h"
#include <vector>
#include "Utils.h"
#include <iostream>

using namespace std;
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

void Game::render(GAME_STATE state)
{
	m_screen->render(m_windowMap);
}

void Game::update()
{
	render(GAME_STATE::PLAY);
	input();
}

void Game::input()
{
	int x(0), y(0);
	char type(0);

	while (1)
	{
		Borland::GotoXY(0, 15);
		cout << "X Y TYPE(C : 선택 , M : 마킹) : ";
		cin >> type;

		switch (type)
		{
		case 'C':
			searchMine(x, y);
			return;

		case 'M':
			markingMine(x,y);
			return;
		default:
			return;
		}
	}
}

void Game::play()
{
	while (1)
	{
		update();
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

void Game::searchMine(int x, int y)
{
	// 해당 좌표가 지뢰인지 확인한다.
	// 1. 지뢰인 경우 : 게임 오버
	// 2. 지뢰가 이닌 경우 8방향에 대한 지뢰 탐색
	// 2-1 8방향에 지뢰가 1개 이상인 경우 : 해당 좌표에 지뢰의 개수만큼 표시
	// 2-2 8방향에 지뢰가 0개인 경우 : 8방향에 대한 지뢰 탐색 함수를 재귀



}

void Game::markingMine(int x, int y)
{
	// 마킹하려는 좌표가 지뢰가 아니라면 화면의 해당 좌표를 M으로 표시해준다.
}
