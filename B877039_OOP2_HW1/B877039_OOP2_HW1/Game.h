#pragma once

class Screen;


class Game
{
private:
	Screen* m_screen; // 

	int m_score;	  // °ÔÀÓ ½ºÄÚ¾î : Áö·Ú¸¦ ¹âÁö ¾Ê°í ³ĞÈù ¶¥ÀÇ Å©±â
	

public:


private:
	void render();
	void update();
	void input();

public:
	void play();

	Game();
	virtual ~Game();
};

