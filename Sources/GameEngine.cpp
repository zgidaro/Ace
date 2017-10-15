//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/GameEngine.h"

GameEngine::GameEngine()
{
	isGreensTurn = true;
	consecutiveNonAttackMoves = 0;
	board = Board();
}

void GameEngine::run()
{
	board.initializeTokens();

	cout << "Welcome to Bonzee!" << endl << endl;

	cout << "Green plays first!" << endl << endl;

	board.print();

	int winner = 0;

	while (consecutiveNonAttackMoves < 10 && winner==0)
	{
		if (isGreensTurn)
		{
			cout << "Green, please enter your move: ";
		}
		else
		{
			cout << "Red, please enter your move: ";
		}

		string moveFrom;
		string moveTo;

		cin >> moveFrom >> moveTo;

		Board::Point pointFrom = Board::ParseString(moveFrom);
		Board::Point pointTo = Board::ParseString(moveTo);

		
		while (!isMoveValid(pointFrom, pointTo))
		{
			cout << "Sorry, that move is invalid. Please enter another move: ";
			cin >> moveFrom >> moveTo;
			pointFrom = Board::ParseString(moveFrom);
			pointTo = Board::ParseString(moveTo);
		}

		board.applyMove(pointFrom, pointTo);

		winner = board.checkWinner();
		isGreensTurn = !isGreensTurn;
//		consecutiveNonAttackMoves++;

		board.print();
	}

		announceWinner(winner);
}

bool GameEngine::isMoveValid(Board::Point point, Board::Point newPoint)
{
	if (checkPointBounds(point) && checkPointBounds(newPoint)) {
		return board.isCorrectColour(isGreensTurn, point) && board.isSpaceEmpty(newPoint) && board.isMoveValid(point, newPoint);
	}
	else {
		cout << "please enter a move within the board bounds" << endl;
		return false;
	}
}

void GameEngine::announceWinner(int winner) 
{
	if (winner == 1)
	{
		cout << " Green Player Wins !" << endl;
	}
	else if (winner == 2)
	{
		cout << "Red Player Wins !" << endl;
	}
	else 
	{
		cout << "It's a Draw !" << endl;
	}

}

bool GameEngine::checkPointBounds(Board::Point p) 
{
	return(p.row > -1 && p.row < 5 && p.col > -1 && p.col < 9);
}