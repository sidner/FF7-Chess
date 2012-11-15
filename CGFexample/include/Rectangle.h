#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Primitive.h"

class Rectangle: public Primitive {
	public:
		Rectangle(float x1, float x2, float y1, float y2);
		float x1,x2,y1,y2;
		void draw();
};

#endif
