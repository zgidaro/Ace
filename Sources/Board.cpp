//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/Board.h"

Board::Board(){ //creating the black and white board
    bool isBlack = true;
    for(int row = 0;row <5;row++){
        for(int col = 0; col < 9; col++){
            Point newPoint;
            newPoint.row = row;
            newPoint.col = col;
            newPoint.isBlack = isBlack;
            isBlack = !isBlack;
            newPoint.token = nullptr;
            board[row][col] = newPoint;
        }
    }
}

//TODO:print method for the Board
void Board::initializeTokens(){

    for(int i=0; i < 2; i++) {
        for (int j = 0; j < 9; j++) {
            Token tRed(j,i,'R');
            tokenRed.push_back(tRed);
        }
    }
    for (int j = 0; j < 4; j++) {
        Token tGreen(j, 2, 'G');
        tokenGreen.push_back(tGreen);
    }
    for (int j = 5; j < 9; j++) {
        Token tRed(j, 2, 'R');
        tokenRed.push_back(tRed);
    }
    for(int i=3; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            Token tGreen(j, i, 'G');
            tokenGreen.push_back(tGreen);
        }
    }

    //testing to see if tokens were initialized
//    for (int i = 0; i < tokenRed.size(); i++ )
//    {
//        cout << tokenRed[i].getRow() << endl;
//    }

    UpdateBoard(tokenGreen, tokenRed);

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

bool Board::isSpaceEmpty(Board::Point newPoint)
{
    return board[newPoint.col][newPoint.row].token == nullptr;
}

bool Board::isMoveValid(Board::Point point, Board::Point newPoint)
{
    // Check if move is in diagonal and return true if the space is black
    if ((point.col == newPoint.col + 1 && (point.row == newPoint.row + 1 || point.row == newPoint.row - 1))
        || (point.col == newPoint.col - 1 && (point.row == newPoint.row + 1 || point.row == newPoint.row - 1)))
    {
        return board[point.col][point.row].isBlack;
    }

    // Check if move horizontal
    if (point.col == newPoint.col + 1 || point.col == newPoint.col - 1)
    {
        return true;
    }

    // Check if move is vertical
    return point.row == newPoint.row + 1 || point.row == newPoint.row - 1;

}

void Board::print()
{
    cout << "   1  2  3  4  5  6  7  8  9" << endl;
    for (int j = 0; j < 5; ++j)
    {
        cout << GetCharFromInt(j) << "  ";
        for (int i = 0; i < 9; ++i)
        {
            Token * tok = board[j][i].token;
            if (tok != nullptr)
            {
                cout << board[j][i].token->getColour();
            }
            else
            {
                cout << " ";
            }

            if (board[j][i].isBlack)
            {
                cout << "\' ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

const Board::Point Board::ParseString(string pos)
{
    Point point;
    point.col = GetIntFromChar(pos[0]);
    point.row = pos[1] - '0';
    point.row -= 1;
    point.token = nullptr;
    return point;
}

void Board::applyMove(Board::Point point, Board::Point newPoint)
{
    Token *token = board[point.col][point.row].token;
    token->setColumn(newPoint.col);
    token->setRow(newPoint.row);

    board[newPoint.col][newPoint.row].token = token;
    board[point.col][point.row].token = nullptr;

//    applyAttack(point, newPoint);

    UpdateBoard(tokenGreen, tokenRed);
}

bool Board::isCorrectColour(bool isGreensTurn, Board::Point point)
{
    return (isGreensTurn && board[point.col][point.row].token->getColour() == 'G')
            || (!isGreensTurn && board[point.col][point.row].token->getColour() == 'R');
}

void Board::applyAttack(Board::Point pointFrom, Board::Point pointTo)
{
    Token *attacking = board[pointTo.col][pointTo.row].token;

    if ((pointFrom.col == pointTo.col - 1) && board[pointTo.col+1][pointTo.row].token->getColour() !=  attacking->getColour())
    {
        for (int i = pointTo.col+1; i < 5; ++i)
        {
            if (board[i][pointTo.row].token->getColour() == attacking->getColour())
            {
                break;
            }

            Token *defending = board[i][pointTo.row].token;
            defending = nullptr;
        }

        return;
    }
}

const int Board::GetIntFromChar(char letter)
{
    switch (letter)
    {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        default:
            return -1;
    }
}

const char Board::GetCharFromInt(int number)
{
    switch (number)
    {
        case 0:
            return 'A';
        case 1:
            return 'B';
        case 2:
            return 'C';
        case 3:
            return 'D';
        case 4:
            return 'E';
        default:
            return 'Z';
    }
}
