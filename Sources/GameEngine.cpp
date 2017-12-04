//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/GameEngine.h"

GameEngine::GameEngine()
{
	isGreensTurn = true;
	isHumanVsAi = false;
	
	string playerColor;

	cout << "Welcome to Bonzee!" << endl << endl;

	cout << "Select a playing mode:" << endl;
	cout << "1. Human vs. Human" << endl;
	cout << "2. Human vs. AI" << endl;

	int n;
	cin >> n;

	if (n == 1)
	{
		isHumanVsAi = false;
	}
	else if (n == 2)
	{
		cout << "DO you want the AI to be Red or Green ?" << endl;
		cin >> playerColor;
		if (playerColor == "G" || playerColor == "Green" || playerColor == "green" || playerColor == "g")
		{
			isAIGreen = true;
		}
		else
		{
			isAIGreen = false;
		}
		isHumanVsAi = true;
	}
	consecutiveNonAttackMoves = 0;
	board = Board();
}

void GameEngine::run()
{
	board.initializeTokens();

	cpu = new Player(&board);

	if (isHumanVsAi)
	{
		if (isAIGreen)
		{
			cout << "Green is playing as the CPU" << endl;
		} else
		{
			cout << "Red is playing as the CPU" << endl;
		}
	}


	cout << "Green plays first!" << endl << endl;

	board.print();

	int winner = 0;

	while (consecutiveNonAttackMoves < 10 && winner == 0)
	{
		Board::Point pointFrom;
		Board::Point pointTo;
		Board::Move cpuMove;

		auto start = std::chrono::high_resolution_clock::now();

		//cout << "e(board) = " << cpu->CalculateHeuristic(board.getGreenTokens(), board.getRedTokens()) << endl;

		if (isGreensTurn)
		{
			if (isHumanVsAi && isAIGreen)
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
			if(isHumanVsAi && !isAIGreen)
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

		auto finish = std::chrono::high_resolution_clock::now();

		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
		cout << microseconds.count()/1000000.0 << "s" << endl;
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
