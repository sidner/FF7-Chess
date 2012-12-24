#include "Board.h"
Board::Board ()
{
    GLuint name = SEED;

    float pos [3];
    
    
    
    for (int i = 0; i < BOARDSIZE; i++)
    {
        vector<House*> temp;
        for (int j = 0; j < BOARDSIZE; j++)
        {
            
            pos[0] = 1.1*i;
            pos[1] = 1.1*j;
            pos[2] = 0;
            temp.push_back (new House (++name,pos));
        }
        board.push_back (temp);
        cout << temp.size();
    }
    
    cout << " " << board.size() << endl;
    
    board[5][5]->model = new Model("Cloud.obj");
    
  
}
void
Board::draw ()
{
    glPushMatrix ();
    glTranslatef (0,0,BOARDSIZE*1.1);
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            board[i][j]->draw ();
        }
    }
    glPopMatrix ();
}
string
Board::getPrologString ()
{
    string prolog = "[";
  
    for (int i = 0; i < BOARDSIZE; i++)
    {
        prolog += "[";
        for (int j = 0; j < BOARDSIZE; j++)
            prolog += board[i][j]->getString ();
        
        prolog += "]";
    }
    
    prolog += "]";
    
    return prolog;
}