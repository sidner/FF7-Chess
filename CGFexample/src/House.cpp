#include "House.h"


House::House ()
{
    pos[0]=0;
    pos[1]=0;
    pos[2]=0;
    
    model = NULL;
    
    terrain = '_';
    
    h= new Rectangle (0,1,0,1);
}


void House::draw (){
    h->draw ();
}

string House::getCoords (){
    char temp[9];
    
    if(model == NULL)
    {
        sprintf(temp, "['%s','_']",model->prologRep);
    }
    else
    {
        sprintf(temp, "['_','%s']",terrain);
    }
    
    return (string)temp;
}