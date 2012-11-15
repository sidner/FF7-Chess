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


















