#include "Rectangle.h"

Rectangle::Rectangle(float x1,float x2,float y1,float y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void Rectangle::draw() 
{
	glBegin(GL_QUADS);
		glNormal3f(0,0,1);
		glTexCoord2d(0,0);
		glVertex2f(x1,y1);
		glTexCoord2d(1,0);
		glVertex2f(x2,y1);
		glTexCoord2d(1,1);
		glVertex2f(x2,y2);
		glTexCoord2d(0,1);
		glVertex2f(x1,y2);
	glEnd();
}
