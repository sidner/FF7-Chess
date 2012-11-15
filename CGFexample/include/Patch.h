#ifndef PATCH_H
#define PATCH_H

#include "Primitive.h"
#include <vector>


using namespace std;

class Patch : public Primitive {
public:
    Patch(float OrderU, float OrderV, float partsU, float partsV, GLfloat control,int size, GLfloat ** ctrl);
    GLfloat ** controlpoints;
    float OrderU, OrderV, partsU, partsV;
    GLfloat textpoints[4][2];
    GLfloat colorpoints[4][4];
    GLfloat control;
    void draw();
};

#endif
