#include "../Headers/Player.h"

Player::Player()
{
	tree = new Node();
}

Player::Player(Board * board)
{
	tree = new Node();
	this->board = board;
}

Player::~Player()
{
	delete tree;
	delete board;
}

void Player::setTree(Node * tree)
{
	this->tree = tree;
}

Node *Player::getTree()
{
	return tree;
}

Node * Player::generateTree(Board b, int depth, bool isGreensTurn)
{
	
	Board board = b;
	vector<Board::Move> moves;

	if (isGreensTurn)
		moves = board.nextMoves(board.getGreenTokens());
	else
		moves = board.nextMoves(board.getRedTokens());

	auto * tree = new Node();

	tree->count = (int)moves.size();

	if (depth > 0 && tree->count > 0)
	{
		tree->child = new Node *[tree->count];
		vector<thread> threads;
		for (int i = 0; i < tree->count; ++i)
		{
			threads.emplace_back(&Player::applyMove, this, board, tree, moves, i, depth - 1, isGreensTurn);
		}

		for (int i = 0; i < threads.size(); ++i)
		{
			threads[i].thread::join();
		}
	}
	else
	{
		tree->heuristic = CalculateHeuristic(board.getGreenTokens(), board.getRedTokens());
		tree->child = nullptr;
		tree->count = 0;
	}

	return tree;
}

void Player::applyMove(Board board, Node * tree, vector<Board::Move> moves, int i, int depth, bool isGreensTurn)
{
	board.applyMove(moves[i].from, moves[i].to);

	tree->child[i] = generateTree(board, depth - 1, !isGreensTurn);

	tree->child[i]->addMove(moves[i]);
}

int Player::alphabeta(Node * node, int depth, int alpha, int beta, bool maximizingPlayer)
{
	int v;

	if (depth == 0 || node->count == 0)
		return node->heuristic;

	if (maximizingPlayer)
	{
		v = INT_MIN;
		for (int i = 0; i < node->count; i++)
		{
			v = max(v, alphabeta(node->child[i], depth - 1, alpha, beta, false));
			alpha = max(alpha, v);
			node->heuristic = alpha;
			if (beta <= alpha)
			{
				pruneChildren(node, i);
				break;
			}
		}
		return v;
	}
	else
	{
		v = INT_MAX;
		for (int i = 0; i < node->count; i++)
		{
			v = min(v, alphabeta(node->child[i], depth - 1, alpha, beta, true));
			beta = min(beta, v);
			node->heuristic = beta;
			if (beta <= alpha)
			{
				pruneChildren(node, i);
				break;
			}
		}
		return v;
	}
}

void Player::pruneChildren(Node * node, int keep)
{
	int del = keep + 1;
	if (node->count >= del)
	{
		int count = 0;
		for (int i = del; i < node->count; i++)
		{
			node->child[i] = nullptr;
			count++;
		}
		node->count -= count;
	}
}

int Player::max(int i1, int i2)
{
	return i1 > i2 ? i1 : i2;
}

int Player::min(int i1, int i2)
{
	return i1 < i2 ? i1 : i2;
}


/*
* e(board) = 100 x SUM(horizontal index g) from g = 1 to # green tokens on board
* 			  + 50  x SUM(vertical index g) from g = 1 to # green tokens on board
* 			  - 100 x SUM(horizontal index r) from r = 1 to # red tokens on board
* 			  - 50  x SUM(vertical index r) from r = 1 to # red tokens on board
*/
int Player::CalculateHeuristic(vector<Token> green, vector<Token> red)
{
	int e_board = 0;

//	e_board = (int) green.size() * 100 - (int) red.size() * 100;

	for (int i = 0; i < green.size(); ++i)
	{
		// Check if green is on a black square
//		int row = green[i].getRow() + 1;
//		int col = green[i].getColumn() + 1;
//		if (row % 2 != 0 && col % 2 != 0)
//		{
//			e_board += 50;
//		}
		e_board += (100 * green[i].getRow()) + (50 * green[i].getColumn());
	}

	for (int i = 0; i < red.size(); ++i)
	{
		// Check if red is on a black square
//		int row = red[i].getRow() + 1;
//		int col = red[i].getColumn() + 1;
//		if (row % 2 != 0 && col % 2 != 0)
//		{
//			e_board += 50;
//		}
		e_board -= (100 * red[i].getRow()) + (50 * red[i].getColumn());
	}

	return e_board;
}

Board::Move Player::makeMove(bool isGreensTurn)
{
	int depth = 4;
	Node * tree = generateTree(*board, depth, isGreensTurn);

	//TODO: Have alphabeta return the best move so we avoid using getMoveIndex (alphabeta already calculates the move anyways)
	alphabeta(tree, depth, INT_MIN, INT_MAX, isGreensTurn);

	//get chosen move index
	int index = getMoveIndex(tree, isGreensTurn);
	
	Board::Move *chosenMove = tree->child[index]->move;
	cout << "chosen Move is from: " << Board::GetCharFromInt(chosenMove->from.row) << chosenMove->from.col + 1 << " to: " << Board::GetCharFromInt(chosenMove->to.row) << chosenMove->to.col + 1 << endl;
	cout << "chosen move heuristic is: " << tree->child[index]->heuristic << endl;

	
	return (*chosenMove);
}


bool Player::isParentOfLeaf(Node& subTree)
{	//TODO: loop over children for certain scenarios
	bool ParentOfLeaf = true;
	for (int i = 0; i < subTree.count; i++)
	{
		if (subTree.child)
		{
			if (subTree.child[i]->child != NULL)
			{
				ParentOfLeaf = false;
			}
		}
	}
	return ParentOfLeaf;
}

void Player::MiniMax(Node *tree, bool minimaxTurn)
{
	if (tree == NULL) {
		return;
	}

	if (isParentOfLeaf(*tree))
	{

		//get Max or min node
		Node& MaxorMinNode = computeMaxOrMin(*tree, minimaxTurn);

		//change node value
		changeNodeValue(tree, MaxorMinNode);

	}
	else
	{
		minimaxTurn = !minimaxTurn;
		for (int i = 0; i < tree->count; i++)
		{
			MiniMax(tree->child[i], minimaxTurn);
		}
	}

}
Node & Player::computeMaxOrMin(Node& tree, bool miniMaxPlayerTurn)
{
	if (tree.child)
	{
		if (miniMaxPlayerTurn)
		{
			Node* max = tree.child[0];
			for (int i = 1; i < tree.count; i++)
			{
				if (tree.child[i]->heuristic > max->heuristic)
				{
					max = tree.child[i];
				}
			}
			return *max;
		}
		else
		{
			Node* min = tree.child[0];
			for (int i = 1; i < tree.count; i++)
			{
				if (tree.child[i]->heuristic < min->heuristic)
				{
					min = tree.child[i];
				}
			}
			return *min;
		}

	}

}

void Player::changeNodeValue(Node* tree, Node& minimaxValue)
{
	//cout << minimaxValue.move->from.col << endl;
	//(*tree) = minimaxValue;
	tree->heuristic = minimaxValue.heuristic;
	tree->count = minimaxValue.count;
	tree->child = minimaxValue.child;

}

int Player::getMoveIndex(Node *tree , bool isGreenTurn)
{
	int index = 0;
	if (tree->child) 
	{
		if (isGreenTurn)
		{
			for (int i = 1; i < tree->count; i++)
			{
				if (tree->child[i]->heuristic > tree->child[index]->heuristic)
				{
					index = i;

				}
			}

		}
		else
		{
			for (int i = 1; i < tree->count; i++)
			{
				if (tree->child[i]->heuristic < tree->child[index]->heuristic)
				{
					index = i;
				}
			}

		}

	}
	
	return index;

}






