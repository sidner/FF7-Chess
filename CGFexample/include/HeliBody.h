#ifndef HELIBODY_H
#define HELIBODY_H

#include "Primitive.h"
#include "Appearance.h"
#include "Cylinder.h"
#include "Animation.h"

class HeliBody : public CGFobject {
public:
    float posx,posy,posz;
	float angle;
   	Animation * animacao;
	Animation * animacao2;
	Animation * animacao3;
	Animation * animacao4;
	Animation * animacao5;
	Animation * animacao6;
	Animation * poly;

    HeliBody(Appearance* app, Appearance* app2);
    Appearance* heli_app;
    Appearance* pads_app;
    GLuint disptop,dispbot,feet;
    Cylinder* horizontal;
    Cylinder* vertical1;
    Cylinder* vertical2;
    void draw();
    void update();
};

#endif