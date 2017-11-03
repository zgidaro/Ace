#ifndef ACE_PLAYER_H
#define ACE_PLAYER_H

#include "Board.h"

struct Node
{
	Node ** child;
	int count;
	int heuristic;
};

class Player
{
private:
	Node * tree;
	Board * board;

//	Node * generateTree(Board board, int depth, bool isGreensTurn);
//	void applyMinimax(Node * tree, bool isGreensTurn);
public:
	Player();
	Player(Board*);
	~Player();

	void setTree(Node *);
	Node * getTree();

//	void makeMove(bool isGreensTurn);

	static int CalculateHeuristic(vector<Token> * green, vector<Token> * red);
};


#endif //ACE_PLAYER_H
