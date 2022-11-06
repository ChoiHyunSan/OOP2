#pragma once
#include "GameObject.h"
#include <vector>
using std::vector;

class Bullet :
    public GameObject
{
public:
    Bullet(int x, int y, Screen& screen, InputSystem& input, int dir, vector<GameObject*>& objs) :
        GameObject('*',x + dir * 2, y,screen,input, objs), dir(dir)
    {

    }

    ~Bullet()
    {

     }

private:
    int dir;

    void update() override
    {
        Move();
        crash();
    }

    void Move()
    {
        auto pos = getPos();
        pos = pos + Position(dir, 0);
        setPos(pos);
    }

    void crash()
    {
        vector<GameObject*> objs = getObjsVec();

        for (int i = 0; i < objs.size(); i++)
        {
            if (objs[i]->getPos() == this->getPos() && objs[i] != this)
                objs[i]->setDead();
        }
    }

    void draw() override
    {
        GameObject::draw();
    }


};

