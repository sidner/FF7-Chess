#include "Board.h"
Board::Board (Board* b)
{
    board = b->board;

    for (unsigned int i = 0; i < board.size (); i++)
        for (unsigned int j = 0; j < board[i].size (); j++)
            board[i][j] = new House (*(board[i][j]));

    pieces1 = b->pieces1;
    pieces2 = b->pieces2;
}
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
    }

    //PLAYER 1

    pieces1.push_back (new Model ("Cloud.obj", "R", 0.0));
    pieces1.push_back (new Model ("Red.obj", "K1", 0.0));
    pieces1.push_back (new Model ("Tifa.obj", "P", 0.0));
    pieces1.push_back (new Model ("cid.obj", "L1", 0.0));
    pieces1.push_back (new Model ("cid.obj", "L2", 0.0));
    pieces1.push_back (new Model ("YUFFIE.obj", "E", 0.0));
    pieces1.push_back (new Model ("Cait.obj", "S1", 0.0));
    pieces1.push_back (new Model ("Cait.obj", "S2", 0.0));
    pieces1.push_back (new Model ("Barret.obj", "D", 0.0));
    pieces1.push_back (new Model ("Red.obj", "K2", 0.0));

    board[0][1]->model = pieces1[0];
    board[0][2]->model = pieces1[1];
    board[0][3]->model = pieces1[2];
    board[0][4]->model = pieces1[3];
    board[0][5]->model = pieces1[4];
    board[0][6]->model = pieces1[5];
    board[0][7]->model = pieces1[6];
    board[0][8]->model = pieces1[7];
    board[2][2]->model = pieces1[8];
    board[1][10]->model = pieces1[9];
    board[0][10]->model = new Model ("castelo.obj", "C", 0.0);

    
    
    for (int i = 0; i < pieces1.size (); i++)
    {
        pieces1[i]->angle = 90.0;
    }

    float normal2 = 90.0;
    //PLAYER 2
    pieces2.push_back (new Model ("Cloud.obj", "r", normal2));
    pieces2.push_back (new Model ("Red.obj", "k1", normal2));
    pieces2.push_back (new Model ("Tifa.obj", "p", normal2));
    pieces2.push_back (new Model ("cid.obj", "l1", normal2));
    pieces2.push_back (new Model ("cid.obj", "l2", normal2));
    pieces2.push_back (new Model ("YUFFIE.obj", "e", normal2));
    pieces2.push_back (new Model ("Cait.obj", "s1", normal2));
    pieces2.push_back (new Model ("Cait.obj", "s2", normal2));
    pieces2.push_back (new Model ("Barret.obj", "d", normal2));
    pieces2.push_back (new Model ("Red.obj", "k2", normal2));

    board[13][1]->model = pieces2[0];
    board[13][2]->model = pieces2[1];
    board[13][3]->model = pieces2[2];
    board[13][4]->model = pieces2[3];
    board[13][5]->model = pieces2[4];
    board[13][6]->model = pieces2[5];
    board[13][7]->model = pieces2[6];
    board[13][8]->model = pieces2[7];
    board[11][2]->model = pieces2[8];
    board[12][10]->model = pieces2[9];
    board[13][10]->model = new Model ("castelo.obj", "c", normal2);

    for (int i = 0; i < pieces2.size (); i++)
    {
        pieces2[i]->angle = -90.0;
    }
    
    Model* mountain = new Model("montanha.obj","M",0.0);
    Model* forest = new Model("Pinheiro.obj","F",0.0);
    
    //Insert Mountains here. 14 Mountains!!!
    board[4][8]->model = mountain;
    board[2][13]->model = mountain;
    board[2][6]->model = mountain;
    board[12][5]->model = mountain;
    board[0][12]->model = mountain;
    board[8][8]->model = mountain;
    board[9][5]->model = mountain;
    board[1][1]->model = mountain;
    board[2][9]->model = mountain;
    board[10][3]->model = mountain;
    board[12][9]->model = mountain;
    board[2][12]->model = mountain;
    board[1][2]->model = mountain;
    board[8][2]->model = mountain;
    
    //Insert Forests here. 7 Forests!!!
    board[9][9]->model = forest;
    board[7][12]->model = forest;
    board[13][13]->model = forest;
    board[9][11]->model = forest;
    board[3][9]->model = forest;
    board[1][0]->model = forest;
    board[3][2]->model = forest;
    
    board[4][8]->terrain = 'M';
    board[2][13]->terrain = 'M';
    board[2][6]->terrain = 'M';
    board[12][5]->terrain = 'M';
    board[0][12]->terrain = 'M';
    board[8][8]->terrain = 'M';
    board[9][5]->terrain = 'M';
    board[1][1]->terrain = 'M';
    board[2][9]->terrain = 'M';
    board[10][3]->terrain = 'M';
    board[12][9]->terrain = 'M';
    board[2][12]->terrain = 'M';
    board[1][2]->terrain = 'M';
    board[8][2]->terrain = 'M';
    
    //Insert Forests here. 7 Forests!!!
    board[9][9]->terrain = 'F';
    board[7][12]->terrain = 'F';
    board[13][13]->terrain = 'F';
    board[9][11]->terrain = 'F';
    board[3][9]->terrain = 'F';
    board[1][0]->terrain = 'F';
    board[3][2]->terrain = 'F';
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
bool
Board::checkPlayer (int player, House* house)
{

    cout << "Player at checkPlayer = " << player << endl;
    if (player == 1)
    {
        for (unsigned int i = 0; i < pieces1.size (); i++)
        {
            if (pieces1[i] == house->model)
                return true;
        }
        return false;
    }
    else if (player == 2)
    {
        for (unsigned int i = 0; i < pieces2.size (); i++)
        {
            if (pieces2[i] == house->model)
                return true;
        }
        return false;
    }
}
void
Board::removePiece (int player, Model* toRemove)
{
    if (player == 1)
    {
        for (unsigned int i = 0; i < pieces2.size (); i++)
        {
            if (toRemove == pieces2[i])
            {
                pieces2.erase (pieces2.begin () + i);
            }
        }
    }
    else if (player == 2)
    {
        for (unsigned int i = 0; i < pieces1.size (); i++)
        {
            if (toRemove == pieces1[i])
            {
                pieces1.erase (pieces1.begin () + i);
            }
        }
    }
}
void
Board::resetChecks ()
{
    for (unsigned int i = 0; i < pieces1.size (); i++)
    {
        pieces1[i]->checked = false;
    }
    for (unsigned int i = 0; i < pieces2.size (); i++)
    {
        pieces2[i]->checked = false;
    }
}
void
Board::resetY ()
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if(board[i][j]->model != NULL)
            {
                board[i][j]->model->isPicked = false;
               board[i][j]->model->pos[1] = 0;
                
            }
        }
    }
}