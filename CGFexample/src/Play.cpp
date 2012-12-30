/* 
 * File:   Play.cpp
 * Author: sidner
 * 
 * Created on December 30, 2012, 2:40 AM
 */

#include "Play.h"
Play::Play (Board* board)
{
    boards.push (board);
}
Play::Play (const Play& orig) { }
Play::~Play () { }

Board* Play::getBoard ()
{
    if(!boards.empty ())
        return boards.top();
    else
        return NULL;
}
Model* Play::getModel ()
{
    if(!models.empty ())
        return models.top();
    else
        return NULL;
}
House* Play::getHouse ()
{
    if(!houses.empty ())
        return houses.top();
    else
        return NULL;
}
int Play::getPlayer ()
{
    if(!players.empty ())
        return players.top();
    else
        return 0;
}
void Play::insertPlay (Board* board,Model* model,House* house,int player)
{
    sizeStacks++;
    boards.push (board);
    models.push(model);
    houses.push(house);
    players.push(player);
}

bool Play::removePlay ()
{
    if(boards.size () > 0 && models.size() > 0 && houses.size() > 0 && players.size() > 0)
    {    
        boards.pop ();
        models.pop();
        houses.pop();
        players.pop();
        sizeStacks--;
        return true;
    }
    else
        return false;
}