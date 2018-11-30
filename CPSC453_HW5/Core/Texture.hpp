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

	Texture(StbImage* image, const GLuint slot);

    Texture(GLuint width, GLuint height);

    GLuint GetTextureHandle() const;

	void Enable() const;

	void Disable() const;

	~Texture();
private:

	GLuint textureID;

	GLuint slot;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif