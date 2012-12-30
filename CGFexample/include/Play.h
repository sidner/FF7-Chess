/* 
 * File:   Play.h
 * Author: sidner
 *
 * Created on December 30, 2012, 2:40 AM
 */

#ifndef PLAY_H
#define	PLAY_H

#include "Board.h"

class Play {
public:
    Play(Board* board);
    Play(const Play& orig);
    virtual ~Play();
    void insertBoard(Board* board);
    bool removeBoard();
    Board* getBoard();
private:
    stack<Board*> plays;
};

#endif	/* PLAY_H */

