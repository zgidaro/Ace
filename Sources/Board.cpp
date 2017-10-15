//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/Board.h"

Board::Board(){ //creating the black and white board
    char cur = 'B';
    for(int row = 0;row <5;row++){
        for(int col = 0; col < 9; col++){
            Point newPoint;
            newPoint.row = row;
            newPoint.col = col;
            newPoint.color = cur;
            if(cur == 'B')
                cur = 'W';
            else
                cur = 'B';
            newPoint.token = nullptr;
            board[row][col] = newPoint;
        }
    }
}

//TODO:print method for the Board
void Board::initializeTokens(){

}

void Board::UpdateBoard(vector<Token> &tokenGreen, vector<Token> &tokenRed) { //every time we pass it, reference the token
    for(int i = 0; i < tokenGreen.size(); i++){
        Token *t = &(tokenGreen.at(i));
        board[t->getRow()][t->getColumn()].token = t;
    }
    for(int i = 0; i < tokenRed.size(); i++){
        Token *t = &(tokenRed.at(i));
        board[t->getRow()][t->getColumn()].token = t;
    }
}
Board::~Board(){

}