#include <iostream>
#include "Game.h"

// 1. �����ϰ� ���� ��ġ -> �Ϸ�
// 2. ��ǥ���� �Է��ϸ� �ش� ��ǥ���� 8���⿡ ���ڰ� �ִ��� �˻�
// 3. ������ ������ŭ �Էµ� ��ǥ�� ���� ǥ��
// 4. �ش� ��ǥ�� ���ڶ�� ���ڸ������ ǥ��
// 5. �ش� ��ǥ�� ���ڰ� 0�̶�� 8������ ��ǥ�� ���� ���ڰ˻� ���

using namespace std;


int main()
{
	srand((unsigned int)time(nullptr));

	Game game;

	game.play();

	return 0;
}