#include "Sphere.h"


Sphere::Sphere(float r, int sli, int sta)
{
	radius=r;
	slices=sli;
	stacks=sta;
	quad = gluNewQuadric();		
}

void Sphere::draw() 
{
		gluQuadricTexture(quad,GL_TRUE);
		gluQuadricOrientation(quad,GLU_OUTSIDE);
		gluSphere(quad,radius,slices,stacks);
}
