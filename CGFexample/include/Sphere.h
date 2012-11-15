#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere: public Primitive {
	public:
		float radius;
		int stacks,slices;
		Sphere(float r, int sli, int sta);
		void draw();
		GLUquadric *quad;
};

#endif
