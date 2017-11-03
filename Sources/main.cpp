#include <iostream>
#include "../Headers/GameEngine.h"


using namespace std;

int main()
{
	srand((int)(time(0)));

	GameEngine game;
	game.run();

    return 0;
}