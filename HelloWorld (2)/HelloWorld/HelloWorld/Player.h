#pragma once
#include <conio.h>
#include "GameObject.h"
#include "Bullet.h"
#include "define.h"

class Player :
    public GameObject
{

private:
	Position targetPos;
	bool isTargetMoveOn;
	int dir;

	auto processInput()
	{
		auto pos = getPos();
		if (input.getKeyDown(0x57)) {
			pos.y--;
		}
		else if (input.getKeyDown(0x41)) {
			pos.x--;
			dir = -1;
		}
		else if (input.getKeyDown(0x53)) {
			pos.y++;
		}
		else if (input.getKeyDown(0x44)) {
			pos.x++;
			dir = 1;
		}
		else if (input.getKeyDown(VK_SPACE)){
			shot();
		}

		if (input.getMouseButtonDown(0))
		{
			targetPos = input.getMousePosition();
			isTargetMoveOn = true;
		}

		setPos(pos);
	}

public:
    Player(int x, int y, Screen& screen, InputSystem& input, vector<GameObject*> objs)
		: GameObject('O', x, y, screen, input, objs), targetPos(0,0), isTargetMoveOn(false), dir(1)
	{}

	void moveToTargetPos()
	{
		auto pos = getPos();

		if (pos.x > targetPos.x)
		{
			pos.x--;
			dir = -1;
		}
		else if (pos.x < targetPos.x) 
		{ 
			pos.x++; dir = 1;
		}

		if (pos.y > targetPos.y) pos.y--;
		else if (pos.y < targetPos.y) pos.y++;

		if (pos.x == targetPos.x && pos.y == targetPos.y) isTargetMoveOn = false;

		setPos(pos);
	}

	void shot()
	{
		Bullet* bullet = new Bullet{getPos().x, getPos().y, screen, input, dir , getObjsVec() };
		objects.push_back(bullet);
	}

	void update() override
	{
		processInput();

		if (isTargetMoveOn)
			moveToTargetPos();
	}

	void draw() override
	{	
		GameObject::draw();
		screen.draw(getPos() + Position{0, -1}, 'P');

		if(dir == 1)
			screen.draw(getPos() + Position{1, 0}, '>');
		else
			screen.draw(getPos() + Position{ -1, 0 }, '<');
	}

	
};

