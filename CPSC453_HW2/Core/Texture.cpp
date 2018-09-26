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

Texture::Texture(StbImage* image, const GLuint slot, Shader* shader, const std::string& hook_name)
{
	this->slot = slot;
	this->shader = shader;
	this->hook_name = hook_name;

	/* generate and bind a texture */
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

    /* bind the image data to the texture */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->ReadWidth(), image->ReadHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->ReadImageData());
    glGenerateMipmap(GL_TEXTURE_2D);

	/* clear the bound texture */
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Enable() const
{
	glActiveTexture(this->slot);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	GLuint UID = glGetUniformLocation(this->shader->GetProgramID(), this->hook_name.c_str());
	glUniform1i(UID, this->slot - GL_TEXTURE0);
}

void Texture::Disable() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}

Texture::~Texture()
{
	shader = NULL;
	glDeleteTextures(1, &this->textureID);
}