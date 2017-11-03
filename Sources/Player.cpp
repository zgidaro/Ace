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
