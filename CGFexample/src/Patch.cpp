#include "Patch.h"
#include <iostream>

using namespace std;

Patch::Patch (float OrderU, float OrderV, float partsU, float partsV, GLfloat control, int size, GLfloat ** ctrl)
{
    this->OrderU = OrderU;
    this->OrderV = OrderV;
    this->partsU = partsU;
    this->partsV = partsV;
    this->control = control;

    controlpoints = new GLfloat*[size];
    
    for(int i = 0; i<size;i++)
    {
        controlpoints[i] = new GLfloat[3];
        controlpoints[i][0] = ctrl[i][0];
        
        controlpoints[i][1] = ctrl[i][1];

        controlpoints[i][2] = ctrl[i][2];
    }
    
    colorpoints[0][0] = 0.2;
    colorpoints[0][1] = 0.2;
    colorpoints[0][2] = 0.2;
    colorpoints[0][3] = 0.0;
    colorpoints[1][0] = 0.2;
    colorpoints[1][1] = 0.2;
    colorpoints[1][2] = 0.2;
    colorpoints[1][3] = 0.0;
    colorpoints[2][0] = 0.2;
    colorpoints[2][1] = 0.2;
    colorpoints[2][2] = 0.2;
    colorpoints[2][3] = 0.0;
    colorpoints[3][0] = 0.2;
    colorpoints[3][1] = 0.2;
    colorpoints[3][2] = 0.2;
    colorpoints[3][3] = 0.0;
    
    textpoints[0][0] = 0.0;
    textpoints[0][1] = 0.0;
    textpoints[1][0] = 0.0;
    textpoints[1][1] = 1.0;
    textpoints[2][0] = 1.0;
    textpoints[2][1] = 0.0;
    textpoints[3][0] = 1.0;
    textpoints[3][1] = 1.0;
}
void
Patch::draw ()
{
    glEnable (GL_AUTO_NORMAL);
    glPushMatrix ();

    int size = OrderU*OrderV;
    GLfloat ctrlpoints[size][3];
    
    for(int i = 0; i<size;i++)
    {
        ctrlpoints[i][0] = controlpoints[i][0];
        ctrlpoints[i][1] = controlpoints[i][1];
        ctrlpoints[i][2] = controlpoints[i][2];
    }
    
    glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, OrderU, 0.0, 1.0, OrderU*3, OrderV, &ctrlpoints[0][0]);
    glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);
    
    glEnable (GL_MAP2_VERTEX_3);
    glEnable (GL_MAP2_NORMAL);
    glEnable(GL_MAP2_COLOR_4);
    glEnable(GL_MAP2_TEXTURE_COORD_2);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 1);
    glMapGrid2f (partsU, 0.0, 1.0, partsV, 0.0, 1.0);

    glEvalMesh2 (control, 0, partsU, 0, partsV);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix ();

}