#pragma once
#pragma warning(disable : 4996)
class Screen;

#define COLS 10
#define ROWS 10
#define MINE 'X'
#define MAP 'Q'

// 할거
// 1. 재귀적인 지뢰없는 맵 찾기
// 2. 입력값 받기
// 3. 게임 외관꾸미기
// 4. 게임오버 상태 만들기

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

	int m_score;	  // 게임 스코어 : 지뢰를 밟지 않고 넓힌 땅의 크기
	

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

