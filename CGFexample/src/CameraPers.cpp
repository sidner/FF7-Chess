#include "CameraPers.h"

CameraPers::CameraPers(string id, float near, float far, float angle,float pos[3],float tar[3])
{
	this->id = id;
	this->near=near;
	this->far=far;
	this->angle=angle;
	for(int i=0;i<3;i++)
	{
		position[i]=pos[i];
		target[i]=tar[i];
	}
}

void CameraPers::applyView()
{
	gluLookAt(position[0],position[1],position[2],target[0],target[1],target[2],0,1,0);
}

void CameraPers::updateProjectionMatrix(int width,int height)
{
	float aspect= (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,aspect,near,far);
}
