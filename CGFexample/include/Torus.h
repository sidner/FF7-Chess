#ifndef TORUS_H
#define TORUS_H

#include "Primitive.h"

class Torus: public Primitive {
	public:
		float inner, outer;
		int slices,loops;
		Torus(float in, float out, int sli, int loo);
		void draw();
};

#endif
