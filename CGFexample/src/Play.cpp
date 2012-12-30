/* 
 * File:   Play.cpp
 * Author: sidner
 * 
 * Created on December 30, 2012, 2:40 AM
 */

#include "Play.h"
Play::Play (Board* board)
{
    plays.push (board);
}
Play::Play (const Play& orig) { }
Play::~Play () { }

Board* Play::getBoard ()
{
   // cout << "Size no getBoard = " << plays.size() << endl;
    if(!plays.empty ())
        return plays.top();
    else
        return NULL;
}

void Play::insertBoard (Board* board)
{
    cout << "Size no insertBoard = " << plays.size() << endl;
    plays.push (board);
}

bool Play::removeBoard ()
{
    cout << "Size no removeBoard = " << plays.size() << endl;
    if(plays.size () > 1)
    {    
        plays.pop ();
        return true;
    }
    else
        return false;
}