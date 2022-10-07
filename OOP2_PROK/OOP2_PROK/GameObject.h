#pragma once
#include "define.h"
#include "Utils.h"
#include <iostream>

using namespace std;

class GameObject
{
private:
	Position m_pos;
	char* m_shape;
	Dimension m_dim;

public:
	Position GetPos() const { return m_pos; }
	void SetPos(const Position pos) { this->m_pos = pos; }

	char GetShape()	const { return m_shape[0]; }

	void processInput()
	{
        char key;

        cin >> key;

        Borland::GotoXY(0, 100);
        printf("key is %c %d \n", key, key);

        switch (key)
        {
        case 'w':
            m_pos.y--;
            break;
        case 's':
            m_pos.y++;
            break;
        case 'a':
            m_pos.x--;
            break;
        case 'd':
            m_pos.x++;
            break;
        }
	}

public:
	GameObject(char shape ,int x, int y);
	virtual ~GameObject();

};

