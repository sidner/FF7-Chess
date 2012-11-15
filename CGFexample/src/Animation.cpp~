#include "Animation.h"





double converte(double rad){
	return(180*rad/3.1415);
}










Animation::Animation(float tempo){
this->tempo=tempo;
}


LineAnimation::LineAnimation(float tempo):Animation(tempo){
}

LineAnimation::LineAnimation(float posx,float posy, float posz, float xf,float yf,float zf, float tempo):Animation(tempo){
this->posx=posx;
this->posy=posy;
this->posz=posz;
this->xf=xf;
this->yf=yf;
this->zf=zf;
fim=false;
deltax= (xf-posx)/tempo;

deltay= (yf-posy)/tempo;
deltaz= (zf-posz)/tempo;
angulo = 0;
}



void LineAnimation::update(float &ox,float &oy,float &oz, float &angulo){
//if(ox>xf){ deltax=0; fim=true;}
//if(ox>yf) deltay=0; //fim=true;}
//if(ox>zf) deltaz=0; //fim=true;}
ox+=deltax;
oy+=deltay;
oz+=deltaz;

angulo=converte(atan(ox/oz));



}












PolyAnimation::PolyAnimation(vector<Animation *> vec, float tempo):Animation(tempo)
{
percurso= vec;
indice=0;
}




void PolyAnimation::update(float &ox,float &oy,float &oz, float &angulo){

	
	
	//cout << ox << "          " << percurso[indice]->getX()<< endl;
	if(indice!=percurso.size()-1){

			if(abs(ox)>= percurso[indice]->getX()){
				if(abs(oy)>=percurso[indice]->getY()){
					if(abs(oz)>=percurso[indice]->getZ()){
				indice++;

			}	
		}
	}
}

	percurso[indice]->update(ox,oy,oz,angulo);


}

























/*

Animation::Animation(int tempo, float x,float y,float z){

this->tempo=tempo;
this->x=x;
this->y=y;
this->z=z;

dirX=1;
dirY=1;
dirZ=1;
angulo=0;

}

Animation::Animation(int tempo){
this->tempo=tempo;
dirX=1;
dirY=1;
dirZ=1;
x=0;
y=0;
z=0;
}



void Animation::update(){

}







LineAnimation::LineAnimation(float xi,float xf,float yi,float yf,float zi,float zf,int tempo):Animation(tempo,xi,yi,zi)
{
deltaX=xf-xi;
deltaY=yf-yi;
deltaZ=zf-zi;
this->xf=xf;
this->yf=yf;
this->zf=zf;
active = false;


}





void LineAnimation::update(){
float velocidadeX=deltaX/tempo;
float velocidadeY=deltaY/tempo;
float velocidadeZ=deltaZ/tempo; 


if(xf<x){
dirX=0;
}
/*if(true) dirX=-1;
if(deltaY<0) dirY=-1;
if(deltaZ<0) dirZ=-1;
*/
//if(x==0) dirX=1;

//if(yf<y) dirY=0;
//if(y==0) dirY=1;

//if(zf<z) dirZ=0;
//if(z==0) dirZ=1;
/*x+=dirX*velocidadeX;
y+=dirY*velocidadeY;
z+=dirZ*velocidadeZ;

glTranslated(x,y,z);
//glRotated(x,1,0,0);
//glRotated(y,0,1,0);
//glRotated(z,0,0,1);


}




PolyAnimation::PolyAnimation(vector<Animation *> vec, int tempo):Animation(tempo,0,0,0)
{
pontosControle= vec;
indice=0;
}




void PolyAnimation::update( float &x, float &y, float &z float &r){

	
	float ax,ay,az,bx,by,bz,ax1,ay1,az1, ax2,ay2,az2,bx1,by1,bz1,bx2,by2,bz2;
	float na,nb,abdot;
	
	if(indice!=pontosControle.size()-1){
	
		if(pontosControle[indice]->x == pontosControle[indice]->getxf() )
		  if(pontosControle[indice]->y==pontosControle[indice]->getyf() )
		    if(pontosControle[indice]->z==pontosControle[indice]->getzf()) {		

				ax=pontosControle[indice]->getxf();
				bx=pontosControle[indice+1]->getxf();
			angulo= atan(ax/bx);
				indice++;

			}	
	
	
		}


	pontosControle[indice]->update();


}

*/




