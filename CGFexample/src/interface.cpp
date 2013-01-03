#include "interface.h"


#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];
interface::interface ()
{
    testVar = 0;
    modelPicked = false;
}
void
interface::initGUI ()
{
    int x = 0;

    char l[6];
    char c[9];
    // Check CGFinterface.h and GLUI documentation for the types of controls available
    GLUI_Panel *varPanel = addPanel ("Luzes", 1);
    addColumn ();
    GLUI_Panel *varPanel2 = addPanel ("Cameras", 1);
    addColumn ();
    GLUI_Panel *varPanel3 = addPanel ("Options", 1);
    addColumn ();
    GLUI_Panel *varPanel4 = addPanel("Mode",1);

    GLUI_Listbox *list = addListboxToPanel (varPanel2, "Cameras", &(((DemoScene*) scene)->nr_cams), 1);
    GLUI_Listbox *apps = addListboxToPanel (varPanel2, "Ambiance", &(((DemoScene*) scene)->ambient), 1);
    apps->add_item (0, "NADA");
    apps->add_item (1, "Grass");
    apps->add_item (2, "Earth");
    apps->add_item (3, "Volcano Cracks");

    for (unsigned int i = 0; i < ((DemoScene*) scene)->number; i++)
    {
        sprintf (c, "Camera: %d", i);
        list->add_item (i, c);

    }
    for (int i = 0; i < ((DemoScene *) scene)->nr; i++)
    {


        sprintf (l, "luz: %d", i);
        // You could also pass a reference to a variable from the scene class, if public
        addCheckboxToPanel (varPanel, l, &(((DemoScene *) scene)->lz[x]), 1);
        x++;
        if (x % 2 == 0)
            addColumnToPanel (varPanel);
    }

    addButtonToPanel (varPanel3, "Skip Piece", 4);
    addButtonToPanel (varPanel3, "Undo", 5);
    addColumnToPanel (varPanel3);
    addButtonToPanel (varPanel3, "Movie", 6);
    addButtonToPanel(varPanel3,"Free/Lock Camera",2);
    
    GLUI_Listbox *modes = addListboxToPanel (varPanel4,"Game Modes",&((DemoScene*)scene)->gameMode,1);
    modes->add_item (0,"Player vs Player");
    modes->add_item(1,"Player vs Machine");
    modes->add_item (2,"Machine vs Machine");
    
    addColumnToPanel(varPanel4);
    GLUI_Listbox *diff = addListboxToPanel (varPanel4,"Difficulty Level",&((DemoScene*)scene)->difficulty,1);
    diff->add_item (0,"Easy");
    diff->add_item(1,"Normal");
    diff->add_item (2,"Sephiroth");
}
void
interface::processGUI (GLUI_Control *ctrl)
{
    switch (ctrl->user_id)
    {
    case 2:
    {
        if(((DemoScene*)scene)->mode == PLAY)
            ((DemoScene*)scene)->mode = FREE;
        else if (((DemoScene*)scene)->mode == FREE)
            ((DemoScene*)scene)->mode = PLAY;
        break;
    }
    case 4:
    {
        if (((DemoScene*) scene)->player == PLAYER1)
        {
            ((DemoScene*) scene)->moves1--;
            if (((DemoScene*) scene)->moves1 == 0)
            {
                ((DemoScene*) scene)->player = PLAYER2;
                ((DemoScene*) scene)->moves2 = ((DemoScene*) scene)->board->pieces2.size ();
            }
        }
        else if (((DemoScene*) scene)->player == PLAYER2)
            ((DemoScene*) scene)->moves2--;
            if (((DemoScene*) scene)->moves2 == 0)
            {
                ((DemoScene*) scene)->player = PLAYER1;
                ((DemoScene*) scene)->moves1 = ((DemoScene*) scene)->board->pieces1.size ();
            }       
        break;
    }
    case 5:
    {
        if (((DemoScene*) scene)->plays->sizeStacks > 0)
        {
            ((DemoScene*) scene)->board = ((DemoScene*) scene)->plays->getBoard ();
            ((DemoScene*) scene)->plays->getModel ()->checked = false;
            ((DemoScene*) scene)->plays->getModel ()->pos[1] = 0;
            ((DemoScene*) scene)->plays->getHouse ()->isPicked = false;
            ((DemoScene*) scene)->plays->getHouse ()->model = ((DemoScene*) scene)->plays->getModel ();
            int i = (((DemoScene*) scene)->plays->getHouse ()->name - 100.0) / 14.0;
            int j = (((DemoScene*) scene)->plays->getHouse ()->name - 100.0) - (14 * i);

            ((DemoScene*) scene)->board->board[i][j] = ((DemoScene*) scene)->plays->getHouse ();

            ((DemoScene*) scene)->player = ((DemoScene*) scene)->plays->getPlayer ();
            ((DemoScene*) scene)->moves1 = ((DemoScene*) scene)->board->pieces1.size ();
            ((DemoScene*) scene)->moves2 = ((DemoScene*) scene)->board->pieces2.size ();
            picked = NULL;
            modelPicked = false;
            if (((DemoScene*) scene)->plays->removePlay ())
            {
                cout << "Undo successfull\n";
            }
        }
        else
        {
            cout << "Error. Trying to remove from an empty stack.\n";
        }
        break;
    }
    case 6:
    {
        if (((DemoScene*) scene)->plays->sizeStacks > 0)
        {
            ((DemoScene*) scene)->movie = true;
            stack<Board*> temp = ((DemoScene*) scene)->plays->getBoards ();
            while (!temp.empty ())
            {

                temp.top ()->resetY ();
                ((DemoScene*) scene)->boardsMovie.push (temp.top ());
                ((DemoScene*) scene)->boardsMovie.top ()->resetY ();
                temp.pop ();
            }
        }
        else
            cout << "There is no Movie as there are no plays!!\n";
        break;
    }
    };
}
void
interface::processMouse (int button, int state, int x, int y)
{
    CGFinterface::processMouse (button, state, x, y);
    //int button2, state2, x2, y2, xf, yf;

    // do picking on mouse press (GLUT_DOWN)
    // this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        /*CGFinterface::processMouse (button2, state2, x2, y2);
        if (button2 == GLUT_LEFT_BUTTON && state2 == GLUT_UP)
        {
            /*If button is clicked down on one location and released in a 
            different location, then the coordinates are the average of both.
            xf = abs ((x + x2) / 2);
            yf = abs ((y + y2) / 2);*/
        performPicking (x, y);
        // }
    }

}
void
interface::performPicking (int x, int y)
{
    // Sets the buffer to be used for selection and activate selection mode
    glSelectBuffer (BUFSIZE, selectBuf);
    glRenderMode (GL_SELECT);

    // Initialize the picking name stack
    glInitNames ();

    // The process of picking manipulates the projection matrix
    // so we will be activating, saving and manipulating it
    glMatrixMode (GL_PROJECTION);

    //store current projmatrix to restore easily in the end with a pop
    glPushMatrix ();

    //get the actual projection matrix values on an array of our own to multiply with pick matrix later
    GLfloat projmat[16];
    glGetFloatv (GL_PROJECTION_MATRIX, projmat);

    // reset projection matrix
    glLoadIdentity ();

    // get current viewport and use it as reference for 
    // setting a small picking window of 5x5 pixels around mouse coordinates for picking
    GLint viewport[4];
    glGetIntegerv (GL_VIEWPORT, viewport);

    // this is multiplied in the projection matrix
    gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

    // multiply the projection matrix stored in our array to ensure same conditions as in normal render
    glMultMatrixf (projmat);

    // force scene drawing under this mode
    // only the names of objects that fall in the 5x5 window will actually be stored in the buffer
    ((DemoScene*) scene)->display_select ();

    // restore original projection matrix
    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();

    glFlush ();

    // revert to render mode, get the picking results and process them
    GLint hits;
    hits = glRenderMode (GL_RENDER);
    processHits (hits, selectBuf);
}
void
interface::processHits (GLint hits, GLuint buffer[])
{
    GLuint *ptr = buffer;
    GLuint mindepth = 0xFFFFFFFF;
    GLuint *selected = NULL;
    GLuint nselected;

    // iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
    for (int i = 0; i < hits; i++)
    {
        int num = *ptr;
        ptr++;
        GLuint z1 = *ptr;
        ptr++;
        ptr++;
        if (z1 < mindepth && num > 0)
        {
            mindepth = z1;
            selected = ptr;
            nselected = num;
        }
        for (int j = 0; j < num; j++)
            ptr++;
    }

    // if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
    if (selected != NULL)
    {
        if (selected[0] == 50)
        {
            processLogin (selected);
        }
        else if (selected[0] >= 100) // A House was picked
        {
            processHouse (selected);
        }
    }
    else
        printf ("Nothing selected while picking \n");
}
void
interface::processHouse (GLuint* selected)
{
    cout << selected[0] << endl;
    int i = (selected[0] - 100.0) / 14.0;
    int j = (selected[0] - 100.0) - (14 * i);

    if (!modelPicked)
    {
        cout << "here\n";
        if (!((DemoScene*) scene)->board->board[i][j]->isPicked)
        {
            cout << "then here\n";
            if (((DemoScene*) scene)->board->board[i][j]->model != NULL &&
                ((DemoScene*) scene)->board->checkPlayer (((DemoScene*) scene)->player, ((DemoScene*) scene)->board->board[i][j]) &&
                !((DemoScene*) scene)->board->board[i][j]->model->checked)
            {
                cout << "Player = " << ((DemoScene*) scene)->player << endl;
                cout << "Moves1 = " << ((DemoScene*) scene)->moves1 << endl;
                cout << "Moves2 = " << ((DemoScene*) scene)->moves2 << endl;
                ((DemoScene*) scene)->board->board[i][j]->isPicked = true;
                modelPicked = true;
                picked = ((DemoScene*) scene)->board->board[i][j];
            }
        }
    }
    else
    {
        //Picked the same house, so it de-selects the piece.
        if (((DemoScene*) scene)->board->board[i][j] == picked)
        {
            picked->isPicked = false;
            picked->model->pos[1] = 0;
            modelPicked = false;
            picked = NULL;
        }
        else //Picked a different house while a model was picked, so it checks path
        {
            string answer;
            string request = ((DemoScene*) scene)->getEntireString (picked->model, ((DemoScene*) scene)->board->board[i][j]);

            answer = ((DemoScene*) scene)->connection->speak (request);




            if (answer == "true.\n")
            {

                if (((DemoScene*) scene)->player == PLAYER1)
                {
                    if (((DemoScene*) scene)->moves1 > 1)
                    {
                        move (((DemoScene*) scene)->board->board[i][j]);
                        check_win ();
                        ((DemoScene*) scene)->moves1--;
                    }
                    else
                    {
                        move (((DemoScene*) scene)->board->board[i][j]);
                        check_win ();
                        ((DemoScene*) scene)->moves2 = ((DemoScene*) scene)->board->pieces2.size ();
                        ((DemoScene*) scene)->player = PLAYER2;
                    }
                }
                else if (((DemoScene*) scene)->player == PLAYER2)
                {
                    if (((DemoScene*) scene)->moves2 > 1)
                    {
                        move (((DemoScene*) scene)->board->board[i][j]);
                        check_win ();
                        ((DemoScene*) scene)->moves2--;
                    }
                    else
                    {
                        move (((DemoScene*) scene)->board->board[i][j]);
                        check_win ();
                        ((DemoScene*) scene)->moves1 = ((DemoScene*) scene)->board->pieces1.size ();
                        ((DemoScene*) scene)->board->resetChecks ();
                        ((DemoScene*) scene)->player = PLAYER1;
                    }
                }

            }
            else
            {
                picked->isPicked = false;
                picked->model->pos[1] = 0;
                modelPicked = false;
                picked = NULL;
                cout << false << endl;
            }
        }
    }
}
void
interface::processLogin (GLuint* selected)
{
    ((DemoScene*) scene)->connection = new Connection ("localhost");
    if (((DemoScene*) scene)->connection->connect_server ())
    {
        ((DemoScene*) scene)->mode = PLAY;
        ((DemoScene*) scene)->nr_cams = 0;
    }
    else
    {
        exit (-1);
    }
}
void
interface::move (House* house)
{
    ((DemoScene*) scene)->plays->insertPlay (new Board (((DemoScene*) scene)->board), picked->model, picked, ((DemoScene*) scene)->player);

    if (house->model != NULL)
    {
        ((DemoScene*) scene)->board->removePiece (((DemoScene*) scene)->player, house->model);
    }
    house->model = picked->model;
    picked->model->checked = true;
    picked->model->pos[1] = 0;
    picked->model = NULL;
    picked->isPicked = false;
    picked = NULL;
    modelPicked = false;
}
void
interface::check_win ()
{
    string win = ((DemoScene*)scene)->getWinString();
    
    string answer = ((DemoScene*)scene)->connection->speak (win);
    
    if(answer == "true.\n")
    {
        cout << "Player " << ((DemoScene*)scene)->player << " wins!!" << endl;
        if(((DemoScene*)scene)->player == PLAYER1)
            ((DemoScene*)scene)->materialAppearance->setTexture ("../textures/P1WINS.jpg");
        else
            ((DemoScene*)scene)->materialAppearance->setTexture ("../textures/P2WINS.jpg");
        ((DemoScene*)scene)->mode = WIN;
    }
}