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

	searchMine(3, 5);
	Borland::GotoXY(0, 16);
	cout << "hello" << endl;
	//while (1)
	//{
	//	Borland::GotoXY(0, 15);
	//	cout << "X Y TYPE(C : ���� , M : ��ŷ) : ";
	//	switch (type)
	//	{
	//	case 'C':
	//		return;

	//	case 'M':
	//		markingMine(x,y);
	//		return;
	//	default:
	//		return;
	//	}
	//}
}

void Game::play()
{
	while (1)
	{
		update();
	}
}

// �����ϰ� ���ڸ� ������ �ϴ� �Լ��� ���� ������ �ʿ���
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

void Game::searchMine(const int x, const int y)
{
	int selectIndex = 10 * y + x - 1;
	// �ش� ��ǥ�� �������� Ȯ���Ѵ�.
	// 1. ������ ��� : ���� ����
	// 2. ���ڰ� �̴� ��� 8���⿡ ���� ���� Ž��
	// 2-1 8���⿡ ���ڰ� 1�� �̻��� ��� : �ش� ��ǥ�� ������ ������ŭ ǥ��
	// 2-2 8���⿡ ���ڰ� ���� ��ǥ�� �ִ� ��� :  8���⿡ ���� ���� Ž�� �Լ��� ���

	// ����ã���� ũ�⺸�� ū ���� ���� ��� ����
	if (x < 1 || y < 1 || x > m_nCols || y > m_nRows) return;

	// 1. ������ ��� : ���� ����
	if (m_mineMap[selectIndex] == MINE) { gameOver(); return; }

	researchMine(x, y, 0);
}

void Game::researchMine(const int x, const int y, int vec)
{
	int selectIndex = 10 * y + x - 1 + vec;

	// ����ã���� ���� ���� ���� ��� ����
	if (x < 1 || y < 1 || x > m_nCols || y > m_nRows) return;

	// 2. ���ڰ� �̴� ��� 8���⿡ ���� ���� Ž��
	int a[] = { (-m_nCols - 1) , (-m_nCols), (1 - m_nCols), -1, 1, (m_nCols - 1),m_nCols, (m_nCols + 1) };
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		int index = selectIndex + a[i];
		if(index >= 0)
			if (m_mineMap[index] == MINE) count++;
			else if(m_mineMap[index] == MAP){}
	}

	// 2-1 8���⿡ ���ڰ� 1�� �̻��� ��� : �ش� ��ǥ�� ������ ������ŭ ǥ��
	m_windowMap[selectIndex] = static_cast<char>(count + 48);

	// 2-2 8���⿡ ���ڰ� ���� ��ǥ�� �ִ� ��� : �ش� ��ǥ�� ���� 8���� ���� Ž�� �Լ��� ���
	//int index = selectIndex + a[i];
	//if (index >= 0)
	//if (m_mineMap[selectIndex] == MAP)
	//{
	//	researchMine(x - 1, y - 1, 0);
	//	researchMine(x - 0, y - 1, 0);
	//	researchMine(x + 1, y - 1, 0);
	//	researchMine(x - 1, y + 0, 0);
	//	researchMine(x + 1, y + 0, 0);
	//	researchMine(x - 1, y + 1, 0);
	//	researchMine(x + 0, y + 1, 0);
	//	researchMine(x + 1, y + 1, 0);
	//}
}

void Game::markingMine(int x, int y)
{
	// ��ŷ�Ϸ��� ��ǥ�� ���ڰ� �ƴ϶�� ȭ���� �ش� ��ǥ�� M���� ǥ�����ش�.
}

void Game::gameOver()
{
	cout << "Game Over!" << endl;
}
