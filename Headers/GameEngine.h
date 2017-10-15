//
// Created by Elias Gonzalez on 2017-10-14.
//

#ifndef ACE_GAMEENGINE_H
#define ACE_GAMEENGINE_H

#include "Board.h"
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

    /* void checkMove();
    void checkAvailable();
    void checkPos(); */

private:
	Board board;
	int consecutiveNonAttackMoves;
	bool isGreensTurn;
};


#endif //ACE_GAMEENGINE_H
