#pragma once

#include <iostream>
#include "Utils.h"
#include "Screen.h"
#include "InputSystem.h"
#include <vector>

using std::vector;
using namespace std;

class GameObject
{
	Position	pos;
	char		shape;
	Dimension	dim;
	vector<GameObject*>& objs;
	bool alive = true;

protected:
	InputSystem& input;
	Screen& screen;

public:
	GameObject(char shape, int x, int y, Screen& screen, InputSystem& input, vector<GameObject*>& objs)
		: pos(x, y), shape(shape), dim(1, 1), screen(screen), input(input) , objs(objs)
	{	
	}

	Screen& getScreen() const { return screen; }
	InputSystem& getInput() const { return input; }
	vector<GameObject*>& getObjsVec() const { return objs; }
	bool isDead()const { return !alive; }
	void setDead() { alive = false; }

	virtual ~GameObject() {}

	auto getPos() const { return pos; }

	void setPos(const Position& pos) 
	{ 
		if (screen.checkValidPos(pos) == false) 
			return;
		this->pos.x = pos.x; this->pos.y = pos.y; 
	}

	const auto getShape() const { return shape; }

	virtual void draw()
	{
		screen.draw(pos, shape);
	}

	virtual void update() {}	
	
};

