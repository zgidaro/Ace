#ifndef ACE_PLAYER_H
#define ACE_PLAYER_H

#include "Board.h"
#include <vector>
#include <thread>

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

	int alphabeta(Node * node, int depth, int alpha, int beta, bool maximizingPlayer);
	pair<int, Board::Move*> alphabeta2(Node * node, int depth, int alpha, int beta, bool maximizingPlayer);
	void pruneChildren(Node * node, int keep);
	int max(int, int);
	int min(int, int);

	void applyMove(Board, Node *, vector<Board::Move> moves, int i, int depth, bool isGreensTurn);

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

	static int CalculateHeuristic(vector<Token> green, vector<Token> red, Board board);
	static bool isCorner(int row, int col);
	static bool isEdge(int row, int col);
};


#endif //ACE_PLAYER_H
