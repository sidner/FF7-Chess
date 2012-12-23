#include "Model.h"


Model::Model (string mod)
{
    //Model
    model = NULL;
    char* path = (char*)malloc(sizeof(char)*mod.length()*10);
    sprintf(path, "../obj/%s",mod.c_str ());

    if (!model)
    {
        // this is the call that actualy reads the OBJ and creates the model object
        model = glmReadOBJ (path);

        if (!model) exit (0);
        // This will rescale the object to fit into the unity matrix
        // Depending on your project you might want to keep the original size and positions you had in 3DS Max or GMAX so you may have to comment this.
        glmUnitize (model);
        // These 2 functions calculate triangle and vertex normals from the geometry data.
        // To be honest I had some problem with very complex models that didn't look to good because of how vertex normals were calculated
        // So if you can export these directly from you modeling tool do it and comment these line
        // 3DS Max can calculate these for you and GLM is perfectly capable of loading them
        glmFacetNormals (model);
        glmVertexNormals (model, 90.0);
    }

    pos[0] = 0.0;
    pos[1] = 0.0;
    pos[2] = 0.0;

    isPicked = false;
    
    name = 10;
    prologRep = '_';
}


void Model::draw ()
{
    glPushMatrix();
    glCullFace (GL_FRONT);
    glTranslatef (pos[0],abs(sin(pos[1])),pos[2]);
    glTranslatef(0.6,0.755,0.6);
    glScaled (0.75,0.75,0.75);
    glRotatef(90,0,1,0);
    glmDraw(model, GLM_MATERIAL);
    glCullFace (GL_BACK);
    glPopMatrix();
}

void Model::animate ()
{
    pos[1] = pos[1] + 0.075;
}