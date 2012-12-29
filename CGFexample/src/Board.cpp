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

            pos[0] = 1.1 * i;
            pos[1] = 1.1 * j;
            pos[2] = 0;
            temp.push_back (new House (++name, pos, j, i));
        }
        board.push_back (temp);
        cout << temp.size ();
    }

    
    board[0][1]->model = new Model ("Cloud.obj","R");
    board[0][2]->model = new Model ("Red.obj","R");
    board[0][3]->model = new Model ("Tifa.obj","R");
    board[0][4]->model = new Model ("cid.obj","R");
    board[0][5]->model = new Model ("Cait.obj","R");
    board[0][6]->model = new Model ("YUFFIE.obj","R");
     board[2][2]->model = new Model ("Barret.obj","R");
      board[0][1]->model = new Model ("castelo.obj","R");
    


}
void
Board::draw ()
{
    glPushMatrix ();
    glTranslatef (0, 0, BOARDSIZE * 1.1);
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
        {

            prolog += board[i][j]->getString ();
            if(j!= BOARDSIZE - 1)
                prolog += ",";
        }
        prolog += "]";
        if(i!= BOARDSIZE - 1)
                prolog += ",";
    }

    prolog += "]";

    return prolog;
}