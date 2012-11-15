#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include <map>
#include "No.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Torus.h"
#include "Patch.h"
#include "Plane.h"
#include "Appearance.h"
#include "CGFlight.h"
#include "CameraPers.h"
#include "CameraOrth.h"
#include <iostream>

using namespace std;

class XMLScene
{
public:
	XMLScene(char *filename);
	~XMLScene(){}
	GLclampf colors[4];
	map<string,No*> nodes;
	map<string,Appearance*> appearances;
	map<string,CGFlight*> luzes;
	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	No* root;
	GLenum mode,shade,frontfaceorder,cullface;
	bool cull_enable;
	map<string,CGFcamera*> cameras;
	CGFcamera* camera_init;
	bool Verifica(No* node);
	vector<pair<No*,bool> > temp;
	void GenerateList(No*);
        Appearance* heli_app;
        Appearance* pads_app;
protected:

	TiXmlDocument* doc;

	TiXmlElement* globalElement; 
	TiXmlElement* camerasElement;
	TiXmlElement* lightElement;
	TiXmlElement* appElement;
	TiXmlElement* graphElement;
	
};

#endif
