#pragma once

class Screen;

#define COLS 11
#define ROWS 10

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

	int m_score;	  // °ÔÀÓ ½ºÄÚ¾î : Áö·Ú¸¦ ¹âÁö ¾Ê°í ³ĞÈù ¶¥ÀÇ Å©±â
	

public:


private:
	void init();
	void render();
	void update();
	void input();

private:
	void setMine(char* m_mineMap, const int size);
	void initMap();


public:
	void play();

	Game();
	virtual ~Game();
};

