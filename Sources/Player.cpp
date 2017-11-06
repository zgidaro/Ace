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
		moves = board.nextMoves(*(board.getGreenTokens()));
	else
		moves = board.nextMoves(*(board.getRedTokens()));

	auto * tree = new Node();

	tree->count = (int)moves.size();
	tree->heuristic = CalculateHeuristic(board.getGreenTokens(), board.getRedTokens());


	if (depth > 0 && tree->count > 0)
	{
		tree->child = new Node *[tree->count];
		for (int i = 0; i < tree->count; ++i)
		{
			board.applyMove(moves[i].from, moves[i].to);

			tree->child[i] = generateTree(board, depth - 1, !isGreensTurn);
			
			tree->child[i]->addMove(moves[i]);
			
			board = b;
		}
	}
	else
	{
		
		tree->child = nullptr;
	}

	return tree;
}

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

void Player::makeMove(bool isGreensTurn)
{
	Node * tree = generateTree(*board, 3, isGreensTurn);


	int miniMaxPlayerTurn = isGreensTurn;

	for (int i = 0; i < tree->count; i++) {
		cout<<"child move at "<<i<<" is:"<<tree->child[i]->move->from.row << "-" << tree->child[i]->move->from.col << " to: " << tree->child[i]->move->to.row << "-" << tree->child[i]->move->to.col << endl;
	}

	if (tree != NULL)
	{
		for (int i = 0; i < 2; i++) 
		{

			MiniMax(tree, isGreensTurn);
			cout << "Trial 1:chosn Move is from: " << tree->move->from.row << "-" << tree->move->from.col << " to: " << tree->move->to.row << "-" << tree->move->to.col << endl;
			cout << "Trial 1chosen move heuristic is: " << tree->heuristic << endl;
		}


	}
	int index = getMoveIndex(tree, isGreensTurn);
	Board::Move *chosenMove = tree->child[index]->move;



	//make move
	//cout << "chosen Move is from: " << tree->move->from.row << "-" << tree->move->from.col << " to: " << tree->move->to.row << "-" << tree->move->to.col << endl;
	cout << "chosen Move is from: " << chosenMove->from.row << "-" << chosenMove->from.col << " to: " << chosenMove->to.row << "-" << chosenMove->to.col << endl;
	cout << "chosen move heuristic is: " << tree->heuristic << endl;
	//(*board).applyMove(tree->move->from, tree->move->to);

}

void Player::printTree(Node * tree)
{

	if (!tree)
	{
		return;
	}

	if (tree->child != NULL)
	{

		for (int i = 0; i < tree->count; i++)
		{
			
			if (tree->child != NULL) 
			{
				printTree(tree->child[i]);
			}
		}

	}
	else
	{
		cout << "\n" << endl;
	}


}

bool Player::isParentOfLeaf(Node& subTree)
{	
	return(subTree.child[0]->child == NULL);
}

void Player::MiniMax(Node *tree, bool minimaxTurn)
{
	
	if (isParentOfLeaf(*tree))
	{
		
		//get Max or min node
		Node& MaxorMinNode = computeMaxOrMin(*tree, minimaxTurn);
		//change node value
		changeNodeValue(tree, MaxorMinNode);
		/*for (int i = 0; i < tree->count; i++) {
			cout << "MOVES OF LEAFS" << tree->child[i]->move->from.col << endl;
		}*/
		//cout << "tree move " << tree->move->from.col;
	
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

	if (miniMaxPlayerTurn)
	{
		Node* max = tree.child[0];
		for (int i = 1; i < tree.count; i++)
		{
			if (tree.child[i]->heuristic > max->heuristic)
			{
				max = tree.child[i];
				/*cout << "MAX ROWS" << endl;
				cout << tree.child[i]->move->from.row << " " << tree.child[i]->move->from.col << endl;*/
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

	return index;

}






