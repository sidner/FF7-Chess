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

    //PLAYER 1
    
    pieces1.push_back (new Model ("Cloud.obj", "R",0.0));
    pieces1.push_back (new Model ("Red.obj", "K",0.0));
    pieces1.push_back (new Model ("Tifa.obj", "P",0.0));
    pieces1.push_back (new Model ("cid.obj", "L1",0.0));
    pieces1.push_back (new Model ("cid.obj", "L1",0.0));
    pieces1.push_back (new Model ("YUFFIE.obj", "E",0.0));
    pieces1.push_back (new Model ("Cait.obj", "S1",0.0));
    pieces1.push_back (new Model ("Cait.obj", "S1",0.0));
    pieces1.push_back (new Model ("Barret.obj", "D",0.0));
    pieces1.push_back(new Model ("castelo.obj","C",0.0));
    
    board[0][1]->model = pieces1[0];
    board[0][2]->model = pieces1[1];
    board[0][3]->model = pieces1[2];
    board[0][4]->model = pieces1[3];
    board[0][5]->model = pieces1[4];
    board[0][6]->model = pieces1[5];
    board[0][7]->model = pieces1[6];
    board[0][8]->model = pieces1[7];
    board[2][2]->model = pieces1[8];
    board[0][10]->model = pieces1[9];

    for(int i = 0; i<pieces1.size ();i++)
    {
        pieces1[i]->angle=90.0;
    }

    float normal2 = 90.0;
    //PLAYER 2
    pieces2.push_back (new Model ("Cloud.obj", "r",normal2));
    pieces2.push_back (new Model ("Red.obj", "k",normal2));
    pieces2.push_back (new Model ("Tifa.obj", "p",normal2));
    pieces2.push_back (new Model ("cid.obj", "l1",normal2));
    pieces2.push_back (new Model ("cid.obj", "l1",normal2));
    pieces2.push_back (new Model ("YUFFIE.obj", "e",normal2));
    pieces2.push_back (new Model ("Cait.obj", "s1",normal2));
    pieces2.push_back (new Model ("Cait.obj", "s1",normal2));
    pieces2.push_back (new Model ("Barret.obj", "d",normal2));
    pieces2.push_back (new Model ("castelo.obj", "c",normal2));
    
    board[13][1]->model = pieces2[0];
    board[13][2]->model = pieces2[1];
    board[13][3]->model = pieces2[2];
    board[13][4]->model = pieces2[3];
    board[13][5]->model = pieces2[4];
    board[13][6]->model = pieces2[5];
    board[13][7]->model = pieces2[6];
    board[13][8]->model = pieces2[7];
    board[11][2]->model = pieces2[8];
    board[13][10]->model = pieces2[9];

    for(int i = 0; i<pieces2.size ();i++)
    {
        pieces2[i]->angle=-90.0;
    }

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
            if (j != BOARDSIZE - 1)
                prolog += ",";
        }
        prolog += "]";
        if (i != BOARDSIZE - 1)
            prolog += ",";
    }

    prolog += "]";

    return prolog;
}