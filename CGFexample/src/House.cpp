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
}

House::House (GLuint n,float p[3])
{
    pos[0] = p[0];
    pos[1] = p[1];
    pos[2] = p[2];

    name = n;

    model = NULL;

    terrain = '_';

    h = new Rectangle (0, 1, 0, 1);
}

void
House::draw ()
{
    glPushMatrix ();
    glRotatef (-90.0,1,0,0);
    
    glTranslatef (pos[0],pos[1],pos[2]);
    h->draw ();
    glPopMatrix ();
}
string
House::getString ()
{
    char temp[9];

    if (model == NULL)
    {
        sprintf (temp, "['%s','_']", model->prologRep);
    }
    else
    {
        sprintf (temp, "['_','%s']", terrain);
    }

    return (string) temp;
}