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

//Node * Player::generateTree(Board board, int depth, bool isGreensTurn)
//{
//	vector<Token> tokens;
//
//	if (isGreensTurn)
//		tokens = board.nextMoveTokens(*(board.getGreenTokens()));
//	else
//		tokens = board.nextMoveTokens(*(board.getRedTokens()));
//
//	auto * tree = new Node();
//
//	tree->count = (int) tokens.size();
//	tree->heuristic = CalculateHeuristic(board.getGreenTokens(), board.getRedTokens());
//
//	if (depth > 0 && tree->count > 0)
//	{
//		tree->child = new Node * [tree->count];
//		for (int i = 0; i < tree->count; ++i)
//		{
//			Board::Point p1 = Board::Point();
//			p1.row = 2;
//			p1.col = 3;
//
//			Board::Point p2 = Board::Point();
//			p2.row = 2;
//			p2.col = 4;
//			bool t = board.applyMove(p1, p2);
//			tree->child[i] = generateTree(board, depth - 1, !isGreensTurn);
//		}
//	}
//	else
//	{
//		tree->child = nullptr;
//	}
//
//	return tree;
//}

/*
 * e(board) = 100 x SUM(horizontal index g) from g = 1 to # green tokens on board
 * 			  + 50  x SUM(vertical index g) from g = 1 to # green tokens on board
 * 			  - 100 x SUM(horizontal index r) from r = 1 to # red tokens on board
 * 			  - 50  x SUM(vertical index r) from r = 1 to # red tokens on board
 */
int Player::CalculateHeuristic(vector<Token> * green, vector<Token> * red)
{
	int e_board = 0;

	for (int i = 0; i < (*green).size(); ++i)
	{
		e_board += (100 * (*green)[i].getRow()) + (50 * (*green)[i].getColumn());
	}

	for (int i = 0; i < (*red).size(); ++i)
	{
		e_board -= (100 * (*red)[i].getRow()) + (50 * (*red)[i].getColumn());
	}

	return e_board;
}

//void Player::applyMinimax(Node *tree, bool isGreensTurn)
//{
//	int val = isGreensTurn ? -32767 : 32767;
//	for (int i = 0; i < (*tree).count; ++i)
//	{
//		Node * child = tree->child[i];
//		if (child->heuristic > val && isGreensTurn)
//			val = child->heuristic;
//		else if (child->heuristic < val && !isGreensTurn)
//			val = child->heuristic;
//
//		applyMinimax(child, !isGreensTurn);
//	}
//}

//void Player::makeMove(bool isGreensTurn)
//{
//	Node * tree = generateTree(*board, 3, isGreensTurn);
////	applyMinimax(generateTree(*board, 3), isGreensTurn);
//}
