#include "CameraOrth.h"

CameraOrth::CameraOrth(string id, float near, float far, float left, float right, float top, float bottom)
{
	this->id = id;
	this->near=near;
	this->far=far;
	this->left=left;
	this->right=right;
	this->top=top;
	this->bottom=bottom;
	pos[0]=0;
	pos[1]=0;
	pos[2]=near;
}

void CameraOrth::applyView()
{
	// In the z axis looking at the xy plane
	gluLookAt(pos[0],pos[1],pos[2],0,0,0,0,1,0);
}

void CameraOrth::updateProjectionMatrix(int width,int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left,right,bottom,top,near,far);
}
