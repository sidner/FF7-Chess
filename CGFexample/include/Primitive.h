#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "CGFobject.h"

class Primitive: public CGFobject {
	public:
		virtual void draw() = 0;
};

#endif
