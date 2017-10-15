//
// Created by Elias Gonzalez on 2017-10-14.
//

#ifndef ACE_PLAYER_H
#define ACE_PLAYER_H

#include "Token.h"

class Player {
private:
    vector<Token> tokenGreen;
    vector<Token> tokenRed;
    char playerColour;

public:
    Player();
    Player(char);
    ~Player();

    void initializeTokens();

    void setPlayerColour(char);
    char getPlayerColour();
};


#endif //ACE_PLAYER_H
