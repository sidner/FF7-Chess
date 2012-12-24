/* 
 * File:   Model.h
 * Author: sidner
 *
 * Created on December 23, 2012, 5:35 PM
 */

#ifndef MODEL_H
#define	MODEL_H

#include <string>
#include "glm.h"
#include <cmath>

#include <stdio.h>

using namespace std;

class Model {
public:
    Model(string path);
    ~Model();
    void draw(float pos[3]);
    void animate();
    GLMmodel* model;
    float pos[3];
    bool isPicked;
    GLuint name;
    char prologRep;
};

#endif	/* MODEL_H */

