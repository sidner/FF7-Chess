#ifndef CYLINDER_H
#define CYLINDER_H

#include "Primitive.h"

class Cylinder: public Primitive {
	public:
		float base,top,height;
		int stacks,slices;
		Cylinder(float b, float t, float h, int sli, int sta);
		void draw();
		GLUquadric *quad;
};

#endif
