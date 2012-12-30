
#ifndef HOUSE_H
#define	HOUSE_H

#include "CGF/CGFobject.h"
#include "Rectangle.h"
#include <string>
#include <iostream>
#include "Model.h"
#include "CGFappearance.h"

using namespace std;

class House: public CGFobject
{
public:
    House(GLuint name);
    House(GLuint name,float pos[3],int col,int line);
    void draw();    
    float pos[3];
    GLuint name;
    string getString();
    Rectangle * h;
    Model* model;
    char terrain;
    bool isPicked;
    int col,line;
    CGFappearance* materialAppearance;
};

#endif	/* HOUSE_H */

