//
// Created by Elias Gonzalez on 2017-10-14.
//

#ifndef ACE_BOARD_H
#define ACE_BOARD_H


#include "Token.h"
#include <vector>

using namespace std;

class Board {
public:
    struct Point{
        int row;
        int col;
        bool isBlack;
        Token *token;
    };
    Board();
	~Board();
    void UpdateBoard(vector<Token> &tokenGreen,vector<Token> &tokenRed); //theoretically update the pos(x,y) and color associated to it
    void initializeTokens();
	void print();

	bool isSpaceEmpty(Point);
    bool isMoveValid(Point, Point);
	bool isCorrectColour(bool, Point);
	bool applyMove(Point, Point);
	int checkWinner();
	static const int GetIntFromChar(char);
	static const char GetCharFromInt(int);
	static const Point ParseString(string);

private:
    Point board[5][9]; //creating the board points
    vector<Token> tokenGreen;
    vector<Token> tokenRed;

	bool applyAttack(Point, Point);
	bool deleteGreenToken(int, int);
	bool deleteRedToken(int, int);

	bool applyForwardAttack(Token*, Point, Point);
	bool applyBackwardAttack(Token*, Point, Point);

	bool isDiagonalMove(Point, Point);

	bool verifyAttackAndDeleteToken(Token*, int, int);

	bool isPointValid(int, int);
	bool isAttacking(Token *, Token *);
};


#endif //ACE_BOARD_H
