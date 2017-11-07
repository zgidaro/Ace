//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/GameEngine.h"

GameEngine::GameEngine()
{
	isGreensTurn = true; 
	
	string playerColor;
	//isAIGreen = rand() % 2 > 0;
	cout << "DO you want to be R or G ?" << endl;
	cin >> playerColor;
	if (playerColor == "G" || playerColor == "Green" || playerColor == "green" || playerColor == "g") 
	{
		isAIGreen = true;
	}
	else 
	{
		isAIGreen = false;
	}
	consecutiveNonAttackMoves = 0;
	board = Board();
}

void GameEngine::run()
{
	board.initializeTokens();

	cpu = new Player(&board);

	cout << "Welcome to Bonzee!" << endl << endl;

	if (isAIGreen)
	{
		cout << "Green is playing as the CPU" << endl;
	}

	else
	{
		cout << "Red is playing as the CPU" << endl;
	}


	cout << "Green plays first!" << endl << endl;

	board.print();

	int winner = 0;

	while (consecutiveNonAttackMoves < 10 && winner == 0)
	{
		Board::Point pointFrom;
		Board::Point pointTo;
		Board::Move cpuMove;

		cout << "e(board) = " << cpu->CalculateHeuristic(board.getGreenTokens(), board.getRedTokens()) << endl;

		if (isGreensTurn)
		{
			if (true) 
			{
				cout << "AI will now play as Green ";

				cpuMove = cpu->makeMove(isGreensTurn);
				pointFrom = cpuMove.from;
				pointTo = cpuMove.to;
			}
			else 
			{
				string moveFrom;
				string moveTo;

				cout << "Green, please enter your move: ";

				cin >> moveFrom >> moveTo;

				 pointFrom = Board::ParseString(moveFrom);
				 pointTo = Board::ParseString(moveTo);

				 while (!isMoveValid(pointFrom, pointTo))
				 {
					 cout << "Sorry, that move is invalid. Please enter another move: ";
					 cin >> moveFrom >> moveTo;
					 pointFrom = Board::ParseString(moveFrom);
					 pointTo = Board::ParseString(moveTo);
				 }
			}
			

		}
		else
		{
			if(true)
			{
				cout << "AI will now play as Red ";

				cpuMove = cpu->makeMove(isGreensTurn);
				pointFrom = cpuMove.from;
				pointTo = cpuMove.to;
			}
			else
			{
				string moveFrom;
				string moveTo;

				cout << "Red, please enter your move: ";

				cin >> moveFrom >> moveTo;

				pointFrom = Board::ParseString(moveFrom);
				pointTo = Board::ParseString(moveTo);

				while (!isMoveValid(pointFrom, pointTo))
				{
					cout << "Sorry, that move is invalid. Please enter another move: ";
					cin >> moveFrom >> moveTo;
					pointFrom = Board::ParseString(moveFrom);
					pointTo = Board::ParseString(moveTo);
				}
			}
		}

		if (board.applyMove(pointFrom, pointTo))
			consecutiveNonAttackMoves = 0;
		else
			consecutiveNonAttackMoves++;

		winner = board.checkWinner();
		isGreensTurn = !isGreensTurn;

		board.print();
	}

	announceWinner(winner);
}

bool GameEngine::isMoveValid(Board::Point point, Board::Point newPoint)
{
	if (point.row == newPoint.row && point.col == newPoint.col)
	{
		return false;
	}

	if (board.isSpaceEmpty(point))
	{
		return false;
	}

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
