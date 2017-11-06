#ifndef ACE_PLAYER_H
#define ACE_PLAYER_H

#include "Board.h"
#include <vector>

struct Node
{
	Node ** child;
	int count;
	int heuristic;
	
	Board::Move *move=new Board::Move;

	void addMove(Board::Move m)
	{	
		(*move) = m;
	};
	
};

class Player
{
private:
	Node * tree;
	Board * board;

	Node * generateTree(Board board, int depth, bool isGreensTurn);
public:
	Player();
	Player(Board*);
	~Player();
	
	
	void setTree(Node *);
	Node * getTree();

	Board::Move makeMove(bool isGreensTurn);
	Node & computeMaxOrMin(Node&,bool);
	void changeNodeValue(Node*, Node&);
	void printTree(Node*);
	bool isParentOfLeaf(Node&);
	void MiniMax(Node*, bool);
	int getMoveIndex(Node*, bool);

	static int CalculateHeuristic(vector<Token> * green, vector<Token> * red);
};


#endif //ACE_PLAYER_H
