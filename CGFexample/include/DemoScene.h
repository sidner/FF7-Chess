#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "XMLScene.h"
#include "HeliBody.h"
#include "Pads.h"

class DemoScene : public CGFscene
{
public:
	void init();
	void display();
	void update(long t);
	void activateCamera(int i);
	DemoScene(char* nome);
	~DemoScene();
	int lz[8];
	int nr;
	int number;
	int nr_cams;
        
private:
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
	XMLScene* lsf;
	CGFcamera* def;
	CGFcamera* active;
	vector<CGFcamera*> vec_cameras;
        HeliBody* heli_body;
        Pads* pads;
	Plane * terrain; 
        char nome[40];
};

#endif
