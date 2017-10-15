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

Player::~Player(){

}