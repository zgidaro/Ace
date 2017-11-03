//
// Created by Elias Gonzalez on 2017-10-14.
//

#ifndef ACE_GAMEENGINE_H
#define ACE_GAMEENGINE_H

#include "Board.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class GameEngine {
public:
    GameEngine();
    void run();
	bool isMoveValid(Board::Point, Board::Point);
	void announceWinner(int);
	bool checkPointBounds(Board::Point);
    /* void checkMove();
    void checkAvailable();
    void checkPos(); */

private:
	Player * cpu;
	Player red;
	Player green;
	Board board;
	int consecutiveNonAttackMoves;
	bool isGreensTurn;
	bool isAIGreen;
};


#endif //ACE_GAMEENGINE_H
