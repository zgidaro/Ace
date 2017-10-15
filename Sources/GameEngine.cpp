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

	while (consecutiveNonAttackMoves < 10)
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

		isGreensTurn = !isGreensTurn;
//		consecutiveNonAttackMoves++;

		board.print();
	}
}

bool GameEngine::isMoveValid(Board::Point point, Board::Point newPoint)
{
	return board.isCorrectColour(isGreensTurn, point) && board.isSpaceEmpty(newPoint) && board.isMoveValid(point, newPoint);
}