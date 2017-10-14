//
// Created by Elias Gonzalez on 2017-10-14.
//

#include "../Headers/Board.h"
Board::Board(){
    char cur = 'B';
    for(int row = 0;row <5;row++){
        for(int col = 0; col < 9; col++){
            Point newPoint;
            newPoint.row = row;
            newPoint.col = col;
            newPoint.color = cur;
            if(cur == 'B')
                cur = 'W';
            else
                cur = 'B';
            newPoint.token = nullptr;
        }
    }

}

void Board::UpdateBoard() {

}