#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

/**
file: Texture.hpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include"Common.hpp"
#include"Shader.hpp"
#include "StbImage.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class Texture {
public:

	Texture(StbImage* image, const GLuint slot, Shader* shader, const std::string& hook_name);

	void Enable() const;

	void Disable() const;

	~Texture();
private:

	GLuint textureID;

	GLuint slot;

	Shader* shader;

	/*
		The name of the uniform variable the texture data will be passed to
	*/
	std::string hook_name;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif