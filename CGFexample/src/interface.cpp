#include "interface.h"


#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];
interface::interface ()
{
    testVar = 0;
    modelPicked=false;
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

    GLUI_Listbox *list = addListboxToPanel (varPanel2, "Cameras", &(((DemoScene*) scene)->nr_cams), 1);


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
}
void
interface::processMouse (int button, int state, int x, int y)
{
    CGFinterface::processMouse (button, state, x, y);
    int button2, state2, x2, y2, xf, yf;

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
        if(selected[0] >= 100) // A House was picked
        {
            cout << selected[0] << endl;
            int i = (selected[0] - 100.0) / 14.0;
            int j = (selected[0] - 100.0) - (14*i);
            
            if(!modelPicked)
            {
                if(!((DemoScene*) scene)->board->board[i][j]->isPicked)
                {
                    if(((DemoScene*) scene)->board->board[i][j]->model != NULL)
                    {
                        ((DemoScene*) scene)->board->board[i][j]->isPicked= true;
                        modelPicked = true;
                        picked = ((DemoScene*) scene)->board->board[i][j];
                    }
                }
            }
            else
            {
                //Picked the same house, so it de-selects the piece.
                if(((DemoScene*) scene)->board->board[i][j] == picked)
                {
                    picked->isPicked = false;
                    picked->model->pos[1] = 0;
                    modelPicked = false;
                    picked = NULL;
                }
                else //Picked a different house while a model was picked, so it checks path
                {
                    string answer;
                    string request = ((DemoScene*) scene)->getEntireString (picked->model,((DemoScene*) scene)->board->board[i][j]);
                              
                    answer = ((DemoScene*) scene)->connection->speak (request);
                    
                 
                    
                    
                    if(answer == "true.\n")
                    {  
                       ((DemoScene*) scene)->board->board[i][j]->model=picked->model;
                       picked->model->pos[1] = 0;
                       picked->model=NULL;
                       picked->isPicked=false;
                       picked=NULL;
                       modelPicked=false;
                        cout << true << endl;
                        
                    }
                    else
                    {
                        cout << false << endl;
                    }
                }
            }
        }
        // this should be replaced by code handling the picked object's ID's (stored in "selected"), 
        // possibly invoking a method on the scene class and passing "selected" and "nselected"
        printf ("Picked ID's: ");
        for (int i = 0; i < nselected; i++)
            printf ("%d ", selected[i]);
        printf ("\n");
    }
    else
        printf ("Nothing selected while picking \n");
}
