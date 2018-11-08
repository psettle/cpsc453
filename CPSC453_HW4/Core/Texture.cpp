/**
file: Texture.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include"Texture.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

Texture::Texture(GLuint width, GLuint height)
{
    /* generate and bind a texture */
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    /* bind the image data to the texture */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    /* clear the bound texture */
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetTextureHandle() const
{
    return textureID;
}

void Texture::Enable() const
{
	glActiveTexture(this->slot);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::Disable() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->textureID);
}