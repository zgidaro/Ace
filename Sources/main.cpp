#include <iostream>
#include "../Headers/GameEngine.h"
#include <ctime>


using namespace std;

int main()
{
	srand((int)(time(0)));

	GameEngine game;
	game.run();

	system("pause");
    return 0;
}