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
	//	cout << "X Y TYPE(C : 선택 , M : 마킹) : ";
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

// 랜덤하게 지뢰를 세팅을 하는 함수에 대한 수정이 필요함
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
	// 해당 좌표가 지뢰인지 확인한다.
	// 1. 지뢰인 경우 : 게임 오버
	// 2. 지뢰가 이닌 경우 8방향에 대한 지뢰 탐색
	// 2-1 8방향에 지뢰가 1개 이상인 경우 : 해당 좌표에 지뢰의 개수만큼 표시
	// 2-2 8방향에 지뢰가 없는 좌표가 있는 경우 :  8방향에 대한 지뢰 탐색 함수를 재귀

	// 지뢰찾기의 크기보다 큰 값이 들어올 경우 무시
	if (x < 0 || y < 0 || x > m_nCols || y > m_nRows) return;

	// 1. 지뢰인 경우 : 게임 오버
	if (m_mineMap[selectIndex] == MINE) { gameOver(); return; }

	researchMine(x, y, 0);
}

void Game::researchMine(const int x, const int y, int vec)
{
	int selectIndex = 10 * y + x  + vec;

	// 지뢰찾기의 범위 값이 들어올 경우 무시
	if (x < 0 || y < 0 || x > m_nCols || y > m_nRows) return;

	// 2. 지뢰가 이닌 경우 위치에 따라 연결된 방향에 대한 지뢰 탐색
	vector<int> dirDefault = { (-m_nCols - 1) , (-m_nCols), (1 - m_nCols), -1, 1, (m_nCols - 1),m_nCols, (m_nCols + 1) };
	vector<int> dirRight = { (-m_nCols - 1) , (-m_nCols), - 1, (m_nCols - 1), m_nCols };
	vector<int> dirLeft = {  (-m_nCols), (1 - m_nCols),  1, m_nCols, (m_nCols + 1) };

	vector<int> vIndex;
	vector<int> dirs;

	// 좌표의 위치에 따라 검색할 방향 벡터 컨테이너를 결정
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
			// 지뢰가 설치된 경우 count를 증가
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

	// 2-1 8방향에 지뢰가 1개 이상인 경우 : 해당 좌표에 지뢰의 개수만큼 표시
	m_windowMap[selectIndex] = static_cast<char>(count + 48);

	// 2-2 8방향에 지뢰가 없는 좌표가 있는 경우 : 해당 좌표에 대한 8방향 지뢰 탐색 함수를 재귀
	for (auto index : vIndex)
	{
		researchMine(index % 10, index / 10, 0);
	}

	return;

}

void Game::markingMine(int x, int y)
{
	// 마킹하려는 좌표가 지뢰가 아니라면 화면의 해당 좌표를 M으로 표시해준다.
}

void Game::gameOver()
{
	cout << "Game Over!" << endl;
}
