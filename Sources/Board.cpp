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
    cout << "   1  2  3  4  5  6  7  8  9" << endl;
    for (int j = 0; j < 5; ++j)
    {
        cout << GetCharFromInt(j) << "  ";
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

bool Board::applyMove(Board::Point point, Board::Point newPoint)
{
	bool attacked = false;
    Token *token = board[point.row][point.col].token;
    token->setColumn(newPoint.col);
    token->setRow(newPoint.row);

    board[newPoint.row][newPoint.col].token = token;
    board[point.row][point.col].token = nullptr;

    attacked = applyAttack(point, newPoint);

    UpdateBoard(tokenGreen, tokenRed);

	return attacked;
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

bool Board::applyAttack(Board::Point pointFrom, Board::Point pointTo)
{
    Token *attacking = board[pointTo.row][pointTo.col].token;

	return applyForwardAttack(attacking, pointFrom, pointTo) || applyBackwardAttack(attacking, pointFrom, pointTo);
}

bool Board::isDiagonalMove(Board::Point point, Board::Point newPoint)
{
	if ((point.col == newPoint.col + 1 && (point.row == newPoint.row + 1 || point.row == newPoint.row - 1))
		|| (point.col == newPoint.col - 1 && (point.row == newPoint.row + 1 || point.row == newPoint.row - 1)))
	{
		return board[point.row][point.col].isBlack;
	}

	return false;
}

bool Board::isPointValid(int row, int col)
{
	return row >= 0 && col >= 0;
}

bool Board::isAttacking(Token * attacking, Token * defending)
{
	return defending != nullptr && defending->getColour() != attacking->getColour();
}

bool Board::applyForwardAttack(Token * attacking, Board::Point pointFrom, Board::Point pointTo)
{
	int deleted = 0;
	Token * defending;

	if (isDiagonalMove(pointFrom, pointTo))
	{
		// Forward attack diagonal up right
		if ((pointFrom.row == pointTo.row + 1) && (pointFrom.col == pointTo.col - 1)
				&& isPointValid(pointTo.row-1, pointTo.col+1))
		{
			defending = board[pointTo.row-1][pointTo.col+1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointTo.row - 1;
				int j = pointTo.col + 1;

				while (i >= 0 && j < 9)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i--;
					j++;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Forward attack diagonal up left
		if ((pointFrom.row == pointTo.row + 1) && (pointFrom.col == pointTo.col + 1)
				&& isPointValid(pointTo.row-1, pointTo.col-1))
		{
			defending = board[pointTo.row-1][pointTo.col-1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointTo.row - 1;
				int j = pointTo.col - 1;

				while (i >= 0 && j >= 0)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i--;
					j--;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Forward attack diagonal down left
		if ((pointFrom.row == pointTo.row - 1) && (pointFrom.col == pointTo.col + 1)
				&& isPointValid(pointTo.row+1, pointTo.col-1))
		{
			defending = board[pointTo.row+1][pointTo.col-1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointTo.row + 1;
				int j = pointTo.col - 1;

				while (i < 5 && j >= 0)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i++;
					j--;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Forward attack diagonal down right
		if ((pointFrom.row == pointTo.row - 1) && (pointFrom.col == pointTo.col - 1)
			&& isPointValid(pointTo.row+1, pointTo.col+1))
		{
			defending = board[pointTo.row+1][pointTo.col+1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointTo.row + 1;
				int j = pointTo.col + 1;

				while (i < 5 && j < 9)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i++;
					j++;
				}

				if (deleted > 0)
					return true;
			}
		}
	}
	else
	{
		// Forward attack to the right
		if ((pointFrom.col == pointTo.col - 1) && isPointValid(pointTo.row, pointTo.col+1))
		{
			defending = board[pointTo.row][pointTo.col+1].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointTo.col + 1; i < 9; i++)
				{
					if (verifyAttackAndDeleteToken(attacking, pointTo.row, i))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Forward attack to the left
		if ((pointFrom.col == pointTo.col + 1) && isPointValid(pointTo.row, pointTo.col-1))
		{
			defending = board[pointTo.row][pointTo.col-1].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointTo.col - 1; i >= 0; i--)
				{
					if (verifyAttackAndDeleteToken(attacking, pointTo.row, i))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Forward attack up
		if ((pointFrom.row == pointTo.row + 1) && isPointValid(pointTo.row-1, pointTo.col))
		{
			defending = board[pointTo.row-1][pointTo.col].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointTo.row - 1; i >= 0; i--)
				{
					if (verifyAttackAndDeleteToken(attacking, i, pointTo.col))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Forward attack down
		if ((pointFrom.row == pointTo.row - 1) && isPointValid(pointTo.row+1, pointTo.col))
		{
			defending = board[pointTo.row+1][pointTo.col].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointTo.row + 1; i < 5; i++)
				{
					if (verifyAttackAndDeleteToken(attacking, i, pointTo.col))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}
	}

	return false;
}

bool Board::applyBackwardAttack(Token * attacking, Board::Point pointFrom, Board::Point pointTo)
{
	int deleted = 0;
	Token * defending;

	if (isDiagonalMove(pointFrom, pointTo))
	{
		// Backward attack diagonal up right
		if ((pointFrom.row == pointTo.row + 1) && (pointFrom.col == pointTo.col - 1)
				&& isPointValid(pointFrom.row+1, pointFrom.col-1))
		{
			defending = board[pointFrom.row+1][pointFrom.col-1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointFrom.row + 1;
				int j = pointFrom.col - 1;

				while (i < 5 && j >= 0)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i++;
					j--;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Backward attack diagonal up left
		if ((pointFrom.row == pointTo.row + 1) && (pointFrom.col == pointTo.col + 1)
				&& isPointValid(pointFrom.row+1, pointFrom.col+1))
		{
			defending = board[pointFrom.row+1][pointFrom.col+1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointFrom.row + 1;
				int j = pointFrom.col + 1;

				while (i < 5 && j < 9)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i++;
					j++;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Backward attack diagonal down left
		if ((pointFrom.row == pointTo.row - 1) && (pointFrom.col == pointTo.col + 1)
				&& isPointValid(pointFrom.row-1, pointFrom.col+1))
		{
			defending = board[pointFrom.row-1][pointFrom.col+1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointFrom.row - 1;
				int j = pointFrom.col + 1;

				while (i >= 0 && j < 9)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i--;
					j++;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Backward attack diagonal down right
		if ((pointFrom.row == pointTo.row - 1) && (pointFrom.col == pointTo.col - 1)
				&& isPointValid(pointFrom.row-1, pointFrom.col-1))
		{
			defending = board[pointFrom.row-1][pointFrom.col-1].token;
			if (isAttacking(attacking, defending))
			{
				int i = pointFrom.row - 1;
				int j = pointFrom.col - 1;

				while (i >= 0 && j >= 0)
				{
					if (verifyAttackAndDeleteToken(attacking, i, j))
						deleted++;
					else
						break;

					i--;
					j--;
				}

				if (deleted > 0)
					return true;
			}
		}
	}
	else
	{
		// Backward attack to the right
		if ((pointFrom.col == pointTo.col - 1) && isPointValid(pointFrom.row, pointFrom.col-1))
		{
			defending = board[pointFrom.row][pointFrom.col-1].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointFrom.col - 1; i >= 0; i--)
				{
					if (verifyAttackAndDeleteToken(attacking, pointFrom.row, i))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Backward attack to the left
		if ((pointFrom.col == pointTo.col + 1) && isPointValid(pointFrom.row, pointFrom.col+1))
		{
			defending = board[pointFrom.row][pointFrom.col+1].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointFrom.col + 1; i < 9; i++)
				{
					if (verifyAttackAndDeleteToken(attacking, pointFrom.row, i))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Backward attack up
		if ((pointFrom.row == pointTo.row + 1) && isPointValid(pointFrom.row+1, pointFrom.col))
		{
			defending = board[pointFrom.row+1][pointFrom.col].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointFrom.row + 1; i < 5; i++)
				{
					if (verifyAttackAndDeleteToken(attacking, i, pointFrom.col))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}

		// Backward attack down
		if ((pointFrom.row == pointTo.row - 1) && isPointValid(pointFrom.row-1, pointFrom.col))
		{
			defending = board[pointFrom.row-1][pointFrom.col].token;
			if (isAttacking(attacking, defending))
			{
				for (int i = pointFrom.row - 1; i >= 0; i--)
				{
					if (verifyAttackAndDeleteToken(attacking, i, pointFrom.col))
						deleted++;
					else
						break;
				}

				if (deleted > 0)
					return true;
			}
		}
	}

	return false;
}

bool Board::verifyAttackAndDeleteToken(Token * attacking, int row, int col)
{
	Token * defending = board[row][col].token;
	if (defending == nullptr || defending->getColour() == attacking->getColour())
	{
		return false;
	}

	if (defending->getColour() == 'G')
	{
		board[row][col].token = nullptr;
		return deleteGreenToken(row, col);
	}
	else
	{
		board[row][col].token = nullptr;
		return deleteRedToken(row, col);
	}
}

bool Board::deleteGreenToken(int row, int col)
{
	for (int j = 0; j < tokenGreen.size(); j++)
	{
		Token &token = tokenGreen[j];
		if ((token.getRow() == row) && (token.getColumn() == col))
		{
			tokenGreen.erase(tokenGreen.begin() + j);
			return true;
		}
	}

	return false;
}

bool Board::deleteRedToken(int row, int col)
{
	for (int j = 0; j < tokenRed.size(); j++)
	{
		Token &token = tokenRed[j];
		if ((token.getRow() == row) && (token.getColumn() == col))
		{
			tokenRed.erase(tokenRed.begin() + j);
			return true;
		}
	}

	return false;
}

const int Board::GetIntFromChar(char letter)
{
    switch (letter)
    {
		case 'a':
        case 'A':
            return 0;
		case 'b':
        case 'B':
            return 1;
		case 'c':
        case 'C':
            return 2;
		case 'd':
        case 'D':
            return 3;
		case 'e':
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
