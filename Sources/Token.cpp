//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/Token.h"

Token::Token() {
    column = 0;
    row = '';
    colour = '';
}

Token::Token(int _column, char _row, char _colour) {
    this->setColumn(_column);
    this->setRow(_row);
    this->setColour(_colour);
}

Token::~Token() = default;

void Token::setColumn(int _column) {column = _column;}
void Token::setRow(char _row) {row = _row;}
void Token::setColour(char _colour) {colour = _colour;}

int Token::getColumn() {return column;}
char Token::getRow() {return row;}
char Token::getColour() {return colour;}