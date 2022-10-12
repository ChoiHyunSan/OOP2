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
	m_mineNum(5),
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

	searchMine(0,0);
	Borland::GotoXY(0, 16);
	//cout << "hello" << endl;
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
	int selectIndex = 10 * y + x;
	// �ش� ��ǥ�� �������� Ȯ���Ѵ�.
	// 1. ������ ��� : ���� ����
	// 2. ���ڰ� �̴� ��� 8���⿡ ���� ���� Ž��
	// 2-1 8���⿡ ���ڰ� 1�� �̻��� ��� : �ش� ��ǥ�� ������ ������ŭ ǥ��
	// 2-2 8���⿡ ���ڰ� ���� ��ǥ�� �ִ� ��� :  8���⿡ ���� ���� Ž�� �Լ��� ���

	// ����ã���� ũ�⺸�� ū ���� ���� ��� ����
	if (x < 0 || y < 0 || x > m_nCols || y > m_nRows) return;

	// 1. ������ ��� : ���� ����
	if (m_mineMap[selectIndex] == MINE) { gameOver(); return; }

	researchMine(x, y, 0);
}

void Game::researchMine(const int x, const int y, int vec)
{
	int selectIndex = 10 * y + x  + vec;

	// ����ã���� ���� ���� ���� ��� ����
	if (x < 0 || y < 0 || x > m_nCols || y > m_nRows) return;

	// 2. ���ڰ� �̴� ��� ��ġ�� ���� ����� ���⿡ ���� ���� Ž��
	vector<int> dirDefault = { (-m_nCols - 1) , (-m_nCols), (1 - m_nCols), -1, 1, (m_nCols - 1),m_nCols, (m_nCols + 1) };
	vector<int> dirRight = { (-m_nCols - 1) , (-m_nCols), - 1, (m_nCols - 1), m_nCols };
	vector<int> dirLeft = {  (-m_nCols), (1 - m_nCols),  1, m_nCols, (m_nCols + 1) };

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
			else if (m_windowMap[index] == MAP)
			{
				vIndex.push_back(index);
			}
		}
	}

	// 2-1 8���⿡ ���ڰ� 1�� �̻��� ��� : �ش� ��ǥ�� ������ ������ŭ ǥ��
	m_windowMap[selectIndex] = static_cast<char>(count + 48);

	// 2-2 8���⿡ ���ڰ� ���� ��ǥ�� �ִ� ��� : �ش� ��ǥ�� ���� 8���� ���� Ž�� �Լ��� ���
	for (auto index : vIndex)
	{
		researchMine(index % 10, index / 10, 0);
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
