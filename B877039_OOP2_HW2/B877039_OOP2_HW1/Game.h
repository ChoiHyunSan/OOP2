#pragma once
#pragma warning(disable : 4996)
#include <vector>
using std::vector;
#include "input.h"
class Screen;

#define COLS 10
#define ROWS 10
#define MINE 'X'
#define MAP 'Q'
#define MINENUM 15

// �Ұ�
// 1. ������� ���ھ��� �� ã��
// 2. �Է°� �ޱ�
// 3. ���� �ܰ��ٹ̱�
// 4. ���ӿ��� ���� �����
// 5. �¸� ���� �߰�, Ŭ���� ȭ�� �߰�

enum class GAME_STATE
{
	TITLE = 0,
	PLAY,
	GAME_OVER,
	GAME_CLEAR
};

class Game
{
private:
	Screen* m_screen; // 
	Input	m_input;

	// Screen Scale
	int		m_nCols;
	int		m_nRows;

	// Map
	char*	m_mineMap;
	char*	m_windowMap;
	
	// etc
	int		m_mineNum;
	char*	m_randMineIndex;

	int		m_keyInputX = -1;
	int		m_keyInputY = -1;

	bool    m_isGameOver;

	int		m_score;	  // ���� ���ھ� : ���ڸ� ���� �ʰ� ���� ���� ũ��

private:
	vector<int> dirDefault = { (-m_nCols - 1) , (-m_nCols), (1 - m_nCols), -1, 1, (m_nCols - 1),m_nCols, (m_nCols + 1) };
	vector<int> dirRight = { (-m_nCols - 1) , (-m_nCols), -1, (m_nCols - 1), m_nCols };
	vector<int> dirLeft = { (-m_nCols), (1 - m_nCols),  1, m_nCols, (m_nCols + 1) };

public:


private:
	void init();
	void render(GAME_STATE state);
	void update();
	void input();

private:
	void setMine();
	void initMap();

	int countMine(int selectIndex);

	void markingMine(int x, int y);

	void search(int x, int y);
	void searchMine(int x, int y, int vec);

	bool isSearchAllMine();

	GAME_STATE checkGameState();

private:
	void gameOver();

public:
	void play();

	Game();
	virtual ~Game();
};

