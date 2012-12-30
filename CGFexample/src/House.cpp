#include "House.h"
House::House (GLuint n)
{
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;

    name = n;

    model = NULL;

    terrain = '_';

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

    terrain = '_';

    h = new Rectangle (1, 0, 1, 0);

    float ambA[3] = {0.1, 0.1, 0.1};
    float difA[3] = {0.3, 0.3, 0.3};
    float specA[3] = {0.3, 0.3, 0.3};
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

}
string
House::getString ()
{
    char temp[12];

    if (model == NULL)
    {
        printf ("['_','%c']",terrain);
        sprintf (temp, "['_','%c']",terrain);
    }
    else
    {

        sprintf (temp, "['%s','%c']",model->prologRep, terrain);
    }

    return (string) temp;
}