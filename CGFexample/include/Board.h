/* 
 * File:   Board.h
 * Author: sidner
 *
 * Created on December 23, 2012, 7:14 PM
 */

#ifndef BOARD_H
#define	BOARD_H

#include "House.h"
#include <vector>
#include <iostream>
#include <stack>

#define BOARDSIZE 14
#define SEED 99

using namespace std;

class Board {
public:
    Board();
    Board(Board* board);
    ~Board(){}
    string getPrologString();
    void draw();
    bool checkPlayer(int player, House* house);
    void removePiece(int player, Model* toRemove);
    void resetChecks();
    vector< vector<House*> > board;
    vector<Model*> pieces1;
    vector<Model*> pieces2;
};
#endif	/* BOARD_H */

