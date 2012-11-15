#include "Cylinder.h"


Cylinder::Cylinder(float b, float t, float h, int sli, int sta)
{
	base=b;
	top=t;
	height=h;
	slices=sli;
	stacks=sta;
	quad = gluNewQuadric();
}

void Cylinder::draw() 
{
		gluQuadricTexture(quad,GL_TRUE);
		gluQuadricOrientation(quad, GLU_OUTSIDE);
		gluCylinder(quad, base,top,height,slices,stacks);
		
		//top disk
		glPushMatrix();
			glTranslated(0,0,height);
			gluDisk(quad,0,top,slices,stacks);
		glPopMatrix();
		
		//bottom disk
		glPushMatrix();
			glScaled(-1.0,-1.0,-1.0);
			gluDisk(quad,0,top,slices, stacks);
		glPopMatrix();

}
