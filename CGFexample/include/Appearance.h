#ifndef APPEARANCE_H
#define APPEARANCE_H

/**
 * @file Appearance.h
 * Appearance class of CGF.
 * 
 */

#include <vector>
#include <string>
#include "CGFtexture.h"

using namespace std;

class Appearance
/// This class can be used to store color and material information (including textures) so you can apply them to an object.
{
	public:
		Appearance();								///< Basic constructor
		Appearance(string id,float*, float*, float*, float*, float);	///< Constructor for initializing emissive, ambient, diffuse and specular components (4-float vector each) and shininess coefficient
		Appearance(float*, float*, float*, float);///< Constructor for initializing ambient, diffuse and specular components (4-float vector each) and shininess coefficient
		Appearance(float*);							///< Constructor for initializing material with a single color (for no-lighting environments)
		Appearance(string, int, int);				///< Constructor for initializing with a texture (filename) and wrapping style in s and t directions


		~Appearance();

		bool apply();									///< Applies the material (makes it active for whatever is rendered next)

		void setEmissive(float*);						///< Sets the Emissive component of the material (4-float vector)
		void setAmbient(float*);						///< Sets the Ambient component of the material (4-float vector)
		void setDiffuse(float*);						///< Sets the Diffuse component of the material (4-float vector)
		void setSpecular(float*);						///< Sets the Specular component of the material (4-float vector)
		void setShininess(float);						///< Sets the Shininess coefficient of the material

		void setTexture(string);						///< Loads the texture specified by filename and stores it
		void setTexture(CGFtexture *tp);				///< Assigns a texture preloaded in a CGFtexture instance to this appearance instance. Useful to avoid multiple loading of the same texture for differente appearances (e.g. with different wrapping parameters or material properties)
		void setTextureWrap(int, int);					///< Sets the texture wrapping mode
		void set_lengths(float s, float t); ///< Sets the lenght of s and t variables of texture
		
		string get_t(){return texName;}

	protected:

		string id;

		int materialType;

		float ambient[4];
		float diffuse[4];
		float specular[4];
		float emissive[4];
		float shininess;

		float color[4];

		float length_s, length_t;
		string texName;
		int sWrap, tWrap;

		CGFtexture *texture;
};

#endif
