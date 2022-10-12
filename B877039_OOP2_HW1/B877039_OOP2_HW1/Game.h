#pragma once
#pragma warning(disable : 4996)
class Screen;

#define COLS 10
#define ROWS 10
#define MINE 'X'
#define MAP 'Q'

// �Ұ�
// 1. ������� ���ھ��� �� ã��
// 2. �Է°� �ޱ�
// 3. ���� �ܰ��ٹ̱�
// 4. ���ӿ��� ���� �����

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
	
	// Screen Scale
	int m_nCols;
	int m_nRows;

	// Map
	char* m_mineMap;
	char* m_windowMap;
	
	// etc
	int m_mineNum;
	char* m_randMineIndex;

	int m_score;	  // ���� ���ھ� : ���ڸ� ���� �ʰ� ���� ���� ũ��
	

public:


private:
	void init();
	void render(GAME_STATE state);
	void update();
	void input();

private:
	void setMine();
	void initMap();
	void searchMine(int x, int y);
	void markingMine(int x, int y);

	void researchMine(int x, int y, int vec);
private:
	void gameOver();

public:
	void play();

	Game();
	virtual ~Game();
};

