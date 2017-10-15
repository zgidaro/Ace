//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/Player.h"
Player::Player(){

}
Player::Player(char playerColour){
    playerColour = ' ';
}
void Player::setPlayerColour(char _playerColour){
    playerColour = _playerColour;
}
char Player::getPlayerColour(){
    return playerColour;
}
void Player::initializeTokens(){

}

bool Player::moveToken(int StratPosition, int TargetPosition) {
	//check start position is not empty
	//check starting position cell color
	//check player if move is valid
	//if move is valid , update board
	return false;
}
Player::~Player(){

}