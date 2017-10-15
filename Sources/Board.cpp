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
		if (t != nullptr)
        	board[t->getRow()][t->getColumn()].token = t;
    }
    for(int i = 0; i < tokenRed.size(); i++){
        Token *t = &(tokenRed.at(i));
		if (t != nullptr)
        	board[t->getRow()][t->getColumn()].token = t;
    }
}
Board::~Board(){

}

bool Board::isSpaceEmpty(Board::Point newPoint)
{
    return board[newPoint.row][newPoint.col].token == nullptr;
}

bool Board::isMoveValid(Board::Point point, Board::Point newPoint)
{
    // Check if move is in diagonal and return true if the space is black
    if ((point.col == newPoint.col + 1 && (point.row == newPoint.row + 1 || point.row == newPoint.row - 1))
        || (point.col == newPoint.col - 1 && (point.row == newPoint.row + 1 || point.row == newPoint.row - 1)))
    {
        return board[point.row][point.col].isBlack;
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
    cout << "\e[1m   1  2  3  4  5  6  7  8  9\e[0m" << endl;
    for (int j = 0; j < 5; ++j)
    {
        cout << "\e[1m" << GetCharFromInt(j) << "\e[0m  ";
        for (int i = 0; i < 9; i++)
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
    point.row = GetIntFromChar(pos[0]);
    point.col = pos[1] - '0';
    point.col -= 1;
    point.token = nullptr;
    return point;
}

void Board::applyMove(Board::Point point, Board::Point newPoint)
{
    Token *token = board[point.row][point.col].token;
    token->setColumn(newPoint.col);
    token->setRow(newPoint.row);

    board[newPoint.row][newPoint.col].token = token;
    board[point.row][point.col].token = nullptr;

    applyAttack(point, newPoint);

    UpdateBoard(tokenGreen, tokenRed);
}

int Board::checkWinner() {
	if (tokenRed.size()== 0) 
	{
		return 1;
	}
	if(tokenGreen.size() == 0)
	{
		return 2;
	}
	return 0;
}

bool Board::isCorrectColour(bool isGreensTurn, Board::Point point)
{
    return (isGreensTurn && board[point.row][point.col].token->getColour() == 'G')
            || (!isGreensTurn && board[point.row][point.col].token->getColour() == 'R');
}

void Board::applyAttack(Board::Point pointFrom, Board::Point pointTo)
{
    Token *attacking = board[pointTo.row][pointTo.col].token;

	if (applyForwardAttack(attacking, pointFrom, pointTo))
		return;

	if (applyBackwardAttack(attacking, pointFrom, pointTo))
		return;

}

bool Board::applyForwardAttack(Token * attacking, Board::Point pointFrom, Board::Point pointTo)
{
	// Forward attack to the right
	Token * defending = board[pointTo.row][pointTo.col+1].token;
	if ((pointFrom.col == pointTo.col - 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.col+1; i < 9; i++)
		{
			verifyAttackAndDeleteToken(attacking, pointTo.row, i);
		}

		return true;
	}

	// Forward attack to the left
	defending = board[pointTo.row][pointTo.col-1].token;
	if ((pointFrom.col == pointTo.col + 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.col-1; i >= 0; i--)
		{
			verifyAttackAndDeleteToken(attacking, pointTo.row, i);
		}

		return true;
	}

	// Forward attack up
	defending = board[pointTo.row-1][pointTo.col].token;
	if ((pointFrom.row == pointTo.row + 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.row-1; i >= 0; i--)
		{
			verifyAttackAndDeleteToken(attacking, i, pointTo.col);
		}

		return true;
	}

	// Forward attack down
	defending = board[pointTo.row+1][pointTo.col].token;
	if ((pointFrom.row == pointTo.row - 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.row+1; i < 5; i++)
		{
			verifyAttackAndDeleteToken(attacking, i, pointTo.col);
		}

		return true;
	}

	return false;
}

bool Board::applyBackwardAttack(Token * attacking, Board::Point pointFrom, Board::Point pointTo)
{
	// Backward attack to the right
	Token * defending = board[pointTo.row][pointTo.col-2].token;
	if ((pointFrom.col == pointTo.col - 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.col-2; i >= 0; i--)
		{
			verifyAttackAndDeleteToken(attacking, pointTo.row, i);
		}

		return true;
	}

	// Backward attack to the left
	defending = board[pointTo.row][pointTo.col+2].token;
	if ((pointFrom.col == pointTo.col + 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.col+2; i < 9; i++)
		{
			verifyAttackAndDeleteToken(attacking, pointTo.row, i);
		}

		return true;
	}

	// Backward attack up
	defending = board[pointTo.row-2][pointTo.col].token;
	if ((pointFrom.row == pointTo.row + 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.row-2; i >= 0; i--)
		{
			verifyAttackAndDeleteToken(attacking, i, pointTo.col);
		}

		return true;
	}

	// Backward attack down
	defending = board[pointTo.row+1][pointTo.col].token;
	if ((pointFrom.row == pointTo.row - 1) && defending != nullptr && defending->getColour() != attacking->getColour())
	{
		for (int i = pointTo.row+2; i < 5; i++)
		{
			verifyAttackAndDeleteToken(attacking, i, pointTo.col);
		}

		return true;
	}

	return false;
}

void Board::verifyAttackAndDeleteToken(Token * attacking, int row, int col)
{
	Token * defending = board[row][col].token;
	if (defending == nullptr || defending->getColour() == attacking->getColour())
	{
		return;
	}

	if (defending->getColour() == 'G')
	{
		board[row][col].token = nullptr;
		deleteGreenToken(row, col);
	}
	else
	{
		board[row][col].token = nullptr;
		deleteRedToken(row, col);
	}
}

void Board::deleteGreenToken(int row, int col)
{
	for (int j = 0; j < tokenGreen.size(); j++)
	{
		Token &token = tokenGreen[j];
		if ((token.getRow() == row) && (token.getColumn() == col))
		{
			tokenGreen.erase(tokenGreen.begin() + j);
			break;
		}
	}
}

void Board::deleteRedToken(int row, int col)
{
	for (int j = 0; j < tokenRed.size(); j++)
	{
		Token &token = tokenRed[j];
		if ((token.getRow() == row) && (token.getColumn() == col))
		{
			tokenRed.erase(tokenRed.begin() + j);
			break;
		}
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
