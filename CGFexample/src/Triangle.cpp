#include "Triangle.h"


Triangle::Triangle(float x1,float x2,float x3,float y1,float y2,float y3,float z1,float z2,float z3)
{
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->z1 = z1;
	this->z2 = z2;
	this->z3 = z3;
}


void Triangle::draw() 
{
	glBegin(GL_TRIANGLES);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x3,y3,z3);
	glEnd();
}
