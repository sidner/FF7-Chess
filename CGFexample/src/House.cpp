#include "House.h"


House::House(House* house)
{   
    pos[0] = house->pos[0];
    pos[1] = house->pos[1];
    pos[2] = house->pos[2];
    name = house->name;
    h = house->h;
    terrain = house->terrain;
    model = house->model;
    terrain = house->terrain;
    isPicked = house->isPicked;
    col = house->col;
    line = house->line;
    materialAppearance=house->materialAppearance;    
}
House::House (GLuint n)
{
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;

    name = n;

    model = NULL;

    terrain = NULL;

    h = new Rectangle (0, 1, 0, 1);
    isPicked = false;
}
House::House (GLuint n, float p[3], int c, int l)
{
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];

    col = c;
    line = l;

    name = n;

    model = NULL;

    terrain = NULL;

    h = new Rectangle (1, 0, 1, 0);

    float ambA[3] = {0.1, 0.1, 0.1};
    float difA[3] = {0.1, 0.1, 0.1};
    float specA[3] = {0.1, 0.1, 0.1};
    float shininessA = 0;

    materialAppearance = new CGFappearance (ambA, difA, specA, shininessA);
    isPicked = false;
}
void
House::draw ()
{
    glPushName (name);
    glPushMatrix ();
    glRotatef (-90.0, 1, 0, 0);
    glTranslatef (pos[0], pos[1], pos[2]);
    glFrontFace(GL_CW);
    materialAppearance->apply();
    h->draw ();
    glFrontFace(GL_CCW);
    glPopMatrix ();
    glPopName ();

    if (model != NULL)
    {
        glLoadName (model->name);
        glPushMatrix ();
        if (isPicked)
            model->animate ();
        model->draw (pos);
        glPopMatrix ();
        glPopName ();
    }
    
    if(terrain != NULL)
    {
        glPushMatrix();
        glScaled(0.8,0.8,0.8);
        terrain->draw(pos);
        glPopMatrix();
    }
}
string
House::getString ()
{
    char temp[12];

    if (model == NULL)
    {
        sprintf (temp, "['_','%s']",terrain->prologRep);
    }
    else
    {

        sprintf (temp, "['%s','_']",model->prologRep);
    }

    return (string) temp;
}