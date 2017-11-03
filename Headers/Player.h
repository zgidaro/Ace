#ifndef ACE_PLAYER_H
#define ACE_PLAYER_H

#include "Board.h"

struct Node
{
	Node ** child;
	int count;
	int heuristic;
	/*
	 * e(board) = 100 x SUM(horizontal index g) from g = 1 to # green tokens on board
	 * 			  + 50  x SUM(vertical index g) from g = 1 to # green tokens on board
	 * 			  - 100 x SUM(horizontal index r) from r = 1 to # red tokens on board
	 * 			  - 50  x SUM(vertical index r) from r = 1 to # red tokens on board
	 */
};

class Player
{
private:
	Node * tree;
	Board * board;

public:
	Player();
	Player(Board*);
	~Player();

	void setTree(Node *);
	Node * getTree();
};


#endif //ACE_PLAYER_H
