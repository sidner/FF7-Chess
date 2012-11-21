#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "DemoShader.h"

DemoShader::DemoShader()
{
	init("../shaders/texshader.vert", "../shaders/texshader.frag");
	//init("../shaders/textureDemo2.vert", "../shaders/textureDemo2.frag");

	CGFshader::bind();

	// Initialize parameter in memory
	normScale=0.0;
	wireframe=0;
	
	// Store Id for the uniform "normScale", new value will be stored on bind()
	scaleLoc = glGetUniformLocation(id(), "normScale");

	baseTexture=new CGFtexture("../textures/VolcanoTex1.png");
	secTexture=new CGFtexture("../textures/volcano.png");

	// get the uniform location for the sampler
	baseImageLoc = glGetUniformLocation(id(), "baseTexture");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(baseImageLoc, 0);

	// repeat if you use more textures in your shader(s)
	secImageLoc = glGetUniformLocation(id(), "secTexture");
	glUniform1i(secImageLoc, 1);
}

void DemoShader::bind(void)
{
	if (wireframe)
		glPolygonMode(GL_FRONT, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_FILL);

	CGFshader::bind();

	// update uniforms
	glUniform1f(scaleLoc, normScale);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	baseTexture->apply();

	// do the same for other textures
	glActiveTexture(GL_TEXTURE1);

	secTexture->apply();

	glActiveTexture(GL_TEXTURE0);

}



void DemoShader::update(float time) 
{
	if (tloc!=-1)
		glUniform1f(tloc, time);
}


DemoShader::~DemoShader(void)
{
	delete(baseTexture);
}
