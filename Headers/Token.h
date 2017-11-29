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
	int deleted;


public:
    Token();
    Token(int, int, char);
    ~Token();

    int getColumn();
    int getRow();
    char getColour();
	int getDeleted();

    void setColumn(int);
    void setRow(int);
    void setColour(char);
	void setDeleted(int);
};


#endif //ACE_TOKEN_H
