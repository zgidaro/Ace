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
    int row;
    char colour;


public:
    Token();
    Token(int, int, char);
    ~Token();

    int getColumn();
    int getRow();
    char getColour();

    void setColumn(int);
    void setRow(int);
    void setColour(char);
};


#endif //ACE_TOKEN_H
