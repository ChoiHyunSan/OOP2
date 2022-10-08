#pragma once

class Screen;


class Game
{
private:
	Screen* m_screen; // 

	int m_score;	  // ���� ���ھ� : ���ڸ� ���� �ʰ� ���� ���� ũ��
	

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

