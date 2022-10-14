#include "Game.h"
#include "Screen.h"
#include <vector>
#include "Utils.h"
#include <iostream>
#include <conio.h>
using namespace std;
using std::vector;

Game::Game()
	:
	m_score(0),
	m_nCols(COLS),
	m_nRows(ROWS),
	m_screen(nullptr),
	m_mineNum(15),
	m_randMineIndex(nullptr),
	m_isGameOver(false)
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

	Borland::GotoXY(27, 2);
	cout << "Q : ��ĭ";

	Borland::GotoXY(27, 3);
	cout << "X : ����";

	// Init Map
	initMap();

}

void Game::render(GAME_STATE state)
{

	if(state == GAME_STATE::PLAY)
		m_screen->render(m_windowMap);
	
}

GAME_STATE Game::checkGameState()
{
	int count = 0;
	
	if (m_isGameOver)
		return GAME_STATE::GAME_OVER;

	else
		return GAME_STATE::PLAY;
}

void Game::update()
{

	render(GAME_STATE::PLAY);
	input();
}

// use getch 
void Game::input()
{
	int x(0), y(0);
	char type(0);

	Borland::GotoXY(8, 2);
	cout << "MINE GAME";

	Borland::GotoXY(2, 4);
	cout << "input x : ";
	Borland::GotoXY(2, 5);
	cout << "input y : ";

	x = _getch();

	Borland::GotoXY(2, 4);
	cout << "input x : " << x -48 << endl;
	Borland::GotoXY(2, 5);
	cout << "input y : ";
	y = _getch();

	search(x - 48, y - 48);

	Borland::GotoXY(27, 6);
	cout << "                                     ";
	Borland::GotoXY(27, 6);
	cout << "Prev x : " << x-48;
	Borland::GotoXY(27, 7);
	cout << "                                     ";
	Borland::GotoXY(27, 7);
	cout << "Prev y : " << y-48;
}

void Game::play()
{
	while (1)
	{
		update();
	}
}

void Game::setMine()
{
	int count = 0;
	while (count < m_mineNum)
	{
		m_randMineIndex[count] = rand() % (m_nCols * m_nRows - 1);

		for (int i = 0; i < count; i++)
		{
			if (m_randMineIndex[count] == m_randMineIndex[i])
			{
				count--;
				break;
			}
		}	
		count++;
	}
	for (int i = 0; i < m_mineNum; ++i)
	{
		m_mineMap[m_randMineIndex[i]] = MINE;
	}

}

void Game::initMap()
{
	// Init Map
	m_mineMap = new char[m_nCols * m_nRows + 1];
	m_windowMap = new char[m_nCols * m_nRows + 1];

	// Set NULL Char
	m_mineMap[m_nCols * m_nRows] = '\0';
	m_windowMap[m_nCols * m_nRows] = '\0';

	// init Mine Index
	m_randMineIndex = new char[m_mineNum];

	// Set mineMap
	memset(m_mineMap, MAP, m_nCols * m_nRows);

	setMine();

	// Set windowMap
	memset(m_windowMap, MAP, m_nCols * m_nRows);

}

void Game::search(int x, int y)
{
	int selectIndex = 10 * y + x;

	// ����ã���� ũ�⺸�� ū ���� ���� ��� ����
	if (x < 0 || y < 0 || x > m_nCols || y > m_nRows) return;

	if (m_mineMap[selectIndex] == MINE) { gameOver(); return; }

	searchMine(x, y, 0);
}

int Game::countMine(int selectIndex)
{
	// 2. ���ڰ� �̴� ��� ��ġ�� ���� ����� ���⿡ ���� ���� Ž��
	vector<int> dirs;

	// ��ǥ�� ��ġ�� ���� �˻��� ���� ���� �����̳ʸ� ����
	if (selectIndex % m_nCols == 0)
		dirs = dirLeft;
	else if (selectIndex % m_nCols == m_nCols - 1)
		dirs = dirRight;
	else
		dirs = dirDefault;

	int count = 0;
	for (auto dir : dirs)
	{
		int index = selectIndex + dir;

		if (index >= 0)
		{
			// ���ڰ� ��ġ�� ��� count�� ����
			if (m_mineMap[index] == MINE)
			{
				count++;
			}
		}
	}

	return count;
}

void Game::searchMine(const int x, const int y, int vec)
{
	int selectIndex = 10 * y + x  + vec;

	// ����ã���� ���� ���� ���� ��� ����
	if (x < 0 || y < 0 || x > m_nCols || y > m_nRows) return;

	// 2. ���ڰ� �̴� ��� ��ġ�� ���� ����� ���⿡ ���� ���� Ž��

	vector<int> vIndex;
	vector<int> dirs;

	// ��ǥ�� ��ġ�� ���� �˻��� ���� ���� �����̳ʸ� ����
	if (x == 0)
		dirs = dirLeft;
	else if (x == m_nCols -1)
		dirs = dirRight;
	else
		dirs = dirDefault;

	int count = 0;
	for (auto dir : dirs)
	{
		int index = selectIndex + dir;

		if (index >= 0)
		{
			// ���ڰ� ��ġ�� ��� count�� ����
			if (m_mineMap[index] == MINE)
			{
				count++;
			}
			// ���ڰ� �ƴѰ��
			else 
			{
				if (m_windowMap[index] == MAP)
				{
					vIndex.push_back(index);
				}
			}
		}
	}

	// 2-1 8���⿡ ���ڰ� 1�� �̻��� ��� : �ش� ��ǥ�� ������ ������ŭ ǥ��
	m_windowMap[selectIndex] = static_cast<char>(count + 48);

	// 2-2 8���⿡ ���ڰ� ���� ��ǥ�� �ִ� ��� : �ش� ��ǥ�� ���� 8���� ���� Ž�� �Լ��� ���
	for (auto index : vIndex)
	{
		// ���ڰ� �ƴ� ��ǥ�� �������ڰ� 0�� ��ǥ�� ���ؼ��� ����Լ� ȣ��
		if (countMine(index) == 0)
			searchMine(index % 10, index / 10, 0);
		// �� �ܿ��� ���������� ������ ��Ÿ����.
		else
			m_windowMap[index] = (char)(countMine(index) + 48);
	}

	return;

}

void Game::markingMine(int x, int y)
{
	// ��ŷ�Ϸ��� ��ǥ�� ���ڰ� �ƴ϶�� ȭ���� �ش� ��ǥ�� M���� ǥ�����ش�.
}

void Game::gameOver()
{
	cout << "Game Over!" << endl;
}
