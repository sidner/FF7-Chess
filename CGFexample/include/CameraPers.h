#ifndef CAMERAPERS_H
#define CAMERAPERS_H

#include "CGFcamera.h"
#include <iostream>
#include <string>
#include <GL/glut.h>

using namespace std;

class CameraPers : public CGFcamera
{
	public:
		string id;
		float near,far,angle,left,right,top,bottom,position[3],target[3];
		CameraPers(string id, float near, float far, float angle,float pos[3],float tar[3]); //Constructor for perspective camera
		void applyView();
		void updateProjectionMatrix(int width, int height);
		string get_id(){return id;}
		
};

#endif
