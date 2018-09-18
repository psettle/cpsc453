#ifndef SHADER_H
#define SHADER_H

/**
file: Shader.hpp
brief: declaration of top level system driver
notes:
    Largely Based off of:
    https://github.com/psettle/CrappyChess/blob/master/Shader.h

    (My own code from a hobby project)
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Common.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

class Shader {
public:
	/*
		Initializes the shader
		vShaderFile:
			The fileName of the glsl file with the vertex shader code
		fShaderFile:
			The fileName of the glsl file with the fragment shader code
	*/
	Shader(const std::string& vShaderFile, const std::string& fShaderFile);

	/*
		Tell the openGL state machine to use this shader on vertex arrays until told otherwise
	*/
	void Enable() const;

	/*
		Disable all shaders in the openGL state machine until told otherwise
	*/
	void Disable() const;

	/*
		Get the program ID used on the shader
	*/
	GLuint GetProgramID() const;

	/*
		Clears the allocated memory for this object, which means telling openGL that
		we are done with this shader
	*/
	~Shader();
protected:
	/*
		The id of the compiled shader program, this is the reference openGL gives us to communicate with
	*/
	GLuint programID;

	/*
		Compile a glsl shader
		fileName:
			The fileName of the glsl file holding the shader code
		type:
			The open GL constant for shader types
			one of GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER
		return:
			The shaderID openGL allocates
	*/
	static GLuint CompileShader(const std::string& fileName, GLuint type);

	/*
		Links a compiled vertex shader and fragment shader into a complete openGL shader
		Clears the allocated memory for the shaders after linking them
		vShader:
			The shader id for the vertex shader to link
		fShader:
			The shader id for the fragment shader to link
		return:
			The programID openGL allocates
	*/
	static GLuint LinkProgram(const GLuint vShader, const GLuint fShader);

	/*
		Compiles and the two provided shaders and links them into a shader program
		vShaderFile:
			The fileName of the glsl file with the vertex shader code
		fShaderFile:
			The fileName of the glsl file with the fragment shader code
		return:
			The programID openGL allocates for the program
	*/
	static GLuint BuildProgram(const std::string& vShaderFile, const std::string& fShaderFile);
};

#endif /* SHADER_H */
