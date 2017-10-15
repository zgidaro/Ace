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
    Board();
    void UpdateBoard(vector<Token> &tokenGreen,vector<Token> &tokenRed); //theoretically update the pos(x,y) and color associated to it
    void initializeTokens();
    ~Board();

private:
    struct Point{
        int row;
        int col;
        char color;
        Token *token;
    };
    Point board[5][9]; //creating the board points
};


#endif //ACE_BOARD_H
