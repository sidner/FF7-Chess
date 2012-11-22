#include "HeliBody.h"
#include <iostream>

using namespace std;
HeliBody::HeliBody (Appearance* heli_app, Appearance* pads_app)
{	float posx=0;
	float posy=0;
	float posz=0;
	float angle=0;
	
	animacao = new LineAnimation(0,0,0,0,5,0,100);
	animacao2 = new LineAnimation(0,0,0,15,0,10,100);
	animacao3 = new LineAnimation(0,0,0,0,20,0,200);
	animacao4 = new LineAnimation(0,0,0,20,0,20,100);
	animacao5 = new LineAnimation(0,0,0,50,0,50,100);
	animacao6 = new LineAnimation(0,0,0,0,80,80,100);
	
	vector<Animation*> teste;
	teste.push_back(animacao);
	teste.push_back(animacao2);
	teste.push_back(animacao3);
	teste.push_back(animacao4);
	teste.push_back(animacao5);
	teste.push_back(animacao6);
	poly= new  PolyAnimation(teste,100);

	
    this->heli_app = heli_app;
    this->pads_app = pads_app;
    
   //heli_app->setTexture("../textures/heli3.jpg");
   // pads_app->setTexture("../textures/pads.jpg");
    
    horizontal = new Cylinder (0.5, 0.5, 40, 12, 12);

    vertical1 = new Cylinder (0.5, 0.5, 5, 12, 12);

    vertical2 = new Cylinder (0.5, 0.5, 5, 12, 12);


    GLfloat controlpointsTop[32][3] = {
        {0.2, 0.0, 1.0},
        {0.1, 0.0, 1.0},
        {-0.1, 0.0, 1.0},
        {-0.2, 0.0, 1.0},

        {1.75, 0.0, 0.33},
        {0.75, 3.0, 0.33},
        {-0.75, 3.0, 0.33},
        {-1.75, 0.0, 0.33},

        {0.5, 0.0, -0.33},
        {0.25, 0.5, -0.33},
        {-0.25, 0.5, -0.33},
        {-0.5, 0.0, -0.33},

        {0.5, 0.0, -2.0},
        {0.15, 0.5, -2.0},
        {-0.15, 0.5, -2.0},
        {-0.5, 0.0, -2.0},

        {0.5, 0.0, -2.25},
        {0.15, 0.5, -2.25},
        {-0.15, 0.5, -2.25},
        {-0.5, 0.0, -2.25},

        {0.5, 0.0, -2.5},
        {0.15, 0.5, -2.5},
        {-0.15, 0.5, -2.5},
        {-0.5, 0.0, -2.5},

        {0.5, 0.0, -3.0},
        {0.15, 0.5, -3.0},
        {-0.15, 0.5, -3.0},
        {-0.5, 0.0, -3.0},

        {0.5, 0.0, -3.5},
        {0.0, 1.0, -3.5},
        {0.0, 1.0, -3.5},
        {-0.5, 0.0, -3.5}
    };
    
    GLfloat controlpointsBot[32][3] = {
        {-0.2, 0.0, 1.0},
        {-0.1, 0.0, 1.0},
        {0.1, 0.0, 1.0},
        {0.2, 0.0, 1.0},

        {-1.75, 0.0, 0.33},
        {-0.75, 0.0, 0.33},
        {0.75, 0.0, 0.33},
        {1.75, 0.0, 0.33},

        {-0.5, 0.0, -0.33},
        {-0.25, 0.0, -0.33},
        {0.25, 0.0, -0.33},
        {0.5, 0.0, -0.33},

        {-0.5, 0.0, -2.0},
        {-0.15, 0.0, -2.0},
        {0.15, 0.0, -2.0},
        {0.5, 0.0, -2.0},

        {-0.5, 0.0, -2.25},
        {-0.15, 0.0, -2.25},
        {0.15, 0.0, -2.25},
        {0.5, 0.0, -2.25},

        {-0.5, 0.0, -2.5},
        {-0.15, 0.0, -2.5},
        {0.15, 0.0, -2.5},
        {0.5, 0.0, -2.5},

        {-0.5, 0.0, -3.0},
        {-0.15, 0.0, -3.0},
        {0.15, 0.0, -3.0},
        {0.5, 0.0, -3.0},

        {-0.2, 0.0, -3.5},
        {-0.15, 0.0, -3.5},
        {0.15, 0.0, -3.5},
        {0.2, 0.0, -3.5}
    };
    
    
    GLfloat colorpoints[4][3];
    GLfloat textpoints[4][2];

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

    disptop = glGenLists (2);
    dispbot = glGenLists (2);
    
    feet = glGenLists(2);


    //top part
    glNewList (disptop, GL_COMPILE);

    glEnable (GL_AUTO_NORMAL);
    glPushMatrix ();


    glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 8, &controlpointsTop[0][0]);
    glMap2f (GL_MAP2_COLOR_4, 0.0, 1.0, 4, 2, 0.0, 1.0, 8, 2, &colorpoints[0][0]);
    glMap2f (GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &textpoints[0][0]);

    glEnable (GL_MAP2_VERTEX_3);
    glEnable (GL_MAP2_NORMAL);
    glEnable (GL_MAP2_COLOR_4);
    glEnable (GL_MAP2_TEXTURE_COORD_2);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 1);
    glMapGrid2f (10, 0.0, 1.0, 20, 0.0, 1.0);

    glEvalMesh2 (GL_FILL, 0, 10, 0,20);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix ();

    glEndList ();


    //bottom part
    glNewList (dispbot, GL_COMPILE);

    glEnable (GL_AUTO_NORMAL);
    glPushMatrix ();
    
    //glFrontFace(GL_CW);
    
    glScalef(1,0,1);

    glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 8, &controlpointsBot[0][0]);
    glMap2f (GL_MAP2_COLOR_4, 0.0, 1.0, 4, 2, 0.0, 1.0, 8, 2, &colorpoints[0][0]);
    glMap2f (GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &textpoints[0][0]);

    glEnable (GL_MAP2_VERTEX_3);
    glEnable (GL_MAP2_NORMAL);
    glEnable (GL_MAP2_COLOR_4);
    glEnable (GL_MAP2_TEXTURE_COORD_2);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, 1);
    glMapGrid2f (10, 0.0, 1.0, 20, 0.0, 1.0);

    glEvalMesh2 (GL_FILL, 0, 10, 0,20);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix ();

    glEndList ();
    
    glNewList (feet,GL_COMPILE);
    glPushMatrix();
    pads_app->apply();
    
    glPushMatrix ();
    
    glTranslatef (-2.0, 0.0, -0.0);

    //Verticals
    glPushMatrix ();

    glTranslatef (1.0, -0.5, 1.0);
    glScalef (0.1, 0.1, 0.1);

    //V1
    glPushMatrix ();
    glRotatef (-90, 1, 0, 0);
    vertical1->draw ();
    glPopMatrix ();
    //V2
    glPushMatrix ();
    glTranslatef (0, 0, -40);
    glRotatef (-90, 1, 0, 0);
    vertical2->draw ();
    glPopMatrix ();

    glPopMatrix ();

    //Horizontal
    glPushMatrix ();
    glTranslatef (1.0, -0.5, -3.0);
    glScalef (0.1, 0.1, 0.1);
    horizontal->draw ();
    glPopMatrix ();

    glPopMatrix ();


    //right part
    //Verticals
    glPushMatrix ();

    glTranslatef (1.0, -0.5, 1.0);
    glScalef (0.1, 0.1, 0.1);

    //V1
    glPushMatrix ();
    glRotatef (-90, 1, 0, 0);
    vertical1->draw ();
    glPopMatrix ();
    //V2
    glPushMatrix ();
    glTranslatef (0, 0, -40);
    glRotatef (-90, 1, 0, 0);
    vertical2->draw ();
    glPopMatrix ();

    glPopMatrix ();

    //Horizontal
    glPushMatrix ();
    glTranslatef (1.0, -0.5, -3.0);
    glScalef (0.1, 0.1, 0.1);
    horizontal->draw ();
    glPopMatrix ();
    glPopMatrix ();
    glEndList();
}
void
HeliBody::draw ()
{
 glPushMatrix ();
    glTranslated(posx,posy,posz);
   
	glRotated(angle,0,1,0);
    //glTranslatef(-12,0,0);
    glPushMatrix();
    
    glScalef (2.0, 2.0, 2.0);

    heli_app->apply ();

  glCallList (disptop);
   glCallList (dispbot);

    glPopMatrix ();

	glCallList(feet);
    
    glPopMatrix();
}


void HeliBody::update(){
//angle = animacao->angulo;
poly->update(posx,posy,posz, angle);
//cout << angle << endl;
}