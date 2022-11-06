
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "GameObject.h"
#include "Utils.h"
#include "Screen.h"
#include "InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "define.h"
using namespace std;

int main()
{
	Screen screen(20, 81);
	InputSystem input;

	//static vector<GameObject*> objects;

	Player* player = new Player{ 1,1,screen,input , objects};
	objects.push_back(player);

	while (1)
	{
		screen.clear();
		input.readEveryFrame();
		if (input.getKeyDown(VK_ESCAPE)) break;

		for (const auto& obj : objects)
			obj->update();
		for (const auto& obj : objects)
			obj->draw();

		// alive��� ���� ������ ����� �ش� ������ false�� ��츦 �ݺ������� �˻��Ͽ� ���� ������ ��� vector���� �����Ѵ�.

		for (int i = 0; i < objects.size();)
		{
			vector<GameObject*>::iterator iter = objects.begin() + i;
			if (objects[i]->isDead())
				objects.erase(iter);
			else
				i++;
		}

		screen.render();
	}

	while(objects.empty())
	{
		GameObject* obj = objects.back();
		objects.pop_back();
		delete obj;
	}

	return 0;
}