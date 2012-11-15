#ifndef ANIMATION_H
#define ANIMATION_H

#include "CGFobject.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;



class Animation{
	public:
	float tempo,angulo;
	Animation(float tempo);
	virtual void update(float &ox, float &oy,float &oz,float &angle){}
	virtual float getPosx(){}
	virtual float getPosy(){}
	virtual float getPosz(){}
	virtual bool getfim(){}

	virtual float getX(){}
	virtual float getY(){}
	virtual float getZ(){}
};



class LineAnimation:public Animation{
	public:
	float posx,posy,posz;
	float xf,yf,zf;
	float deltax,deltay,deltaz;
	bool fim;
	LineAnimation(float tempo);
	LineAnimation(float posx,float posy, float posz, float xf,float yf,float zf, float tempo);
	void update(float &ox, float &oy,float &oz, float &angulo);
	bool getFim(){return fim;}
	 float getPosx(){return posx;}
	 float getPosy(){return posy;}
	 float getPosz(){return posz;}

	 float getX(){return xf;}
	 float getY(){return yf;}
	 float getZ(){return zf;}


};




class PolyAnimation:public Animation{
	public:

	vector<Animation *> percurso;
	PolyAnimation(vector<Animation *> percurso,float tempo);
	void update(float &ox,float &oy,float &oz, float &angulo);
	float indice;








};











#endif
