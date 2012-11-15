#include "Torus.h"


Torus::Torus(float in, float out, int sli, int loo)
{
	inner=in;
	outer=out;
	slices=sli;
	loops=loo;
}

void Torus::draw() 
{
	glutSolidTorus(inner,outer,slices,loops);
}
