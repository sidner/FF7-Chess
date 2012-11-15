#ifndef CAMERAORTH_H
#define CAMERAORTH_H

#include "CGFcamera.h"
#include <iostream>
#include <string>
#include <GL/glut.h>

using namespace std;

class CameraOrth : public CGFcamera
{
	public:
		string id;
		float near,far,left,right,top,bottom,pos[3];
		CameraOrth(string id, float near, float far, float left, float right, float top, float bottom);
		void applyView();
		void updateProjectionMatrix(int width, int height);
		string get_id(){return id;}
		
};

#endif
