//
// Created by Elias Gonzalez on 2017-10-14.
//

#ifndef ACE_TOKEN_H
#define ACE_TOKEN_H

#include <iostream>
#include <vector>

using namespace std;

class Token {
private:
    int column;
    char row;
    char colour;


public:
    Token();
    Token(int, char, char);
    ~Token();

    int getColumn();
    char getRow();
    char getColour();

    void setColumn(int);
    void setRow(char);
    void setColour(char);
};


#endif //ACE_TOKEN_H
