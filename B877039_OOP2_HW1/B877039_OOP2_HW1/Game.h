#pragma once

class Screen;

#define COLS 10
#define ROWS 10

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

	int m_score;	  // °ÔÀÓ ½ºÄÚ¾î : Áö·Ú¸¦ ¹âÁö ¾Ê°í ³ÐÈù ¶¥ÀÇ Å©±â
	

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

public:
	void play();

	Game();
	virtual ~Game();
};

