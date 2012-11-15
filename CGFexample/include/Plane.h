#ifndef PLANE_H
#define PLANE_H


#include "Primitive.h"
#include "DemoShader.h"
#include "CGFappearance.h"

class Plane : public Primitive {
public:
	CGFappearance* terrainAppearance;
    Plane(int parts);
    GLfloat controlpoints[4][3];
    int parts;
    GLfloat textpoints[4][2];
    GLfloat colorpoints[4][4];
    void draw();
    DemoShader * vulcao;
     void update();
};

#endif
