#include <iostream>
#include "Pet.h"
#include "Dog.h"
#include "GameObject.h"
#include "Utils.h"
#include "Screen.h"
using namespace std;


int main()
{

    // init player
    GameObject player('X', 3, 3);
    //GameObject monster('Y', 10, 10);

    // init screen
    Screen screen(30, 81);

    while(1)
    {
        char key;

        screen.clear();

        screen.draw(player.GetPos(), player.GetShape());
        //screen.draw(monster.GetPos(), monster.GetShape());

        screen.render();
        
        player.processInput();
    }

    return 0;
}


