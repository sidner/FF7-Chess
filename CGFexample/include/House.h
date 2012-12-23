/* 
 * File:   House.h
 * Author: sidner
 *
 * Created on December 23, 2012, 6:20 PM
 */

#ifndef HOUSE_H
#define	HOUSE_H

#include "CGF/CGFobject.h"
#include "Rectangle.h"
#include <string>
#include "Model.h"

using namespace std;

class House: public CGFobject
{
    House();
    void draw();    
    float pos[3];
    GLuint name;
    string getCoords();
    Rectangle * h;
    Model* model;
    char terrain;
};

#endif	/* HOUSE_H */

