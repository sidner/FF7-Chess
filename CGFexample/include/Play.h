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

    Play() {
        sizeStacks = 0;
    }
    Play(const Play& orig);
    virtual ~Play();
    void insertPlay(Board* board, Model* model,House* house, int player);
    bool removePlay();
    Board* getBoard();
    Model* getModel();
    House* getHouse();
    stack<Board*> getBoards(){return boards;}
    int getPlayer();
    int sizeStacks;
private:
    stack<Board*> boards;
    stack<Model*> models;
    stack<House*>houses;
    stack<int> players;
};

#endif	/* PLAY_H */

