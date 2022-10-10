#include <iostream>
#include "Game.h"

// 1. 랜덤하게 지뢰 설치 -> 완료
// 2. 좌표값을 입력하면 해당 좌표에서 8방향에 지뢰가 있는지 검색
// 3. 지뢰의 개수만큼 입력된 좌표에 숫자 표현
// 4. 해당 좌표가 지뢰라면 지뢰모양으로 표현
// 5. 해당 좌표의 숫자가 0이라면 8방향의 좌표에 대한 지뢰검색 재귀

using namespace std;


int main()
{
	srand((unsigned int)time(nullptr));

	Game game;

	game.play();

	return 0;
}