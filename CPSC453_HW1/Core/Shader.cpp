/**
file: system.hpp
brief: declaration of top level system driver
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include<string>
#include<fstream>

#include "Shader.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/* read text file to string */
static std::string file_get_contents(const std::string& fileName);

/**********************************************************
                       DEFINITIONS
**********************************************************/

Shader::Shader(const std::string& vShaderFile, const std::string& fShaderFile)
{
	/* compile the shader and set the program ID as the result of the build */
	this->programID = Shader::BuildProgram(vShaderFile, fShaderFile);
}

void Shader::Enable() const
{
	glUseProgram(this->programID);
}

void Shader::Disable() const
{
	glUseProgram(0);
}

GLuint Shader::GetProgramID() const
{
	return this->programID;
}

Shader::~Shader()
{
	glDeleteProgram(this->programID);
}

GLuint Shader::CompileShader(const std::string& fileName, GLuint type)
{
    /* allocate a shader */
	GLuint shader;
	shader = glCreateShader(type);
    /* grab the file contents */
	std::string code = file_get_contents(fileName);
	const GLchar* codePtr = code.c_str();
    /* pass the file contents to the shader */
	glShaderSource(shader, 1, &codePtr, NULL);
    /* compile the shader */
	glCompileShader(shader);

    /* check if the compilation was successful, print an error if it failed */
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
    {
		std::cerr << "COMPILE FAILED" << std::endl;
	}
    /* grab the compilation log and print it */
	GLint length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 1)
    {
		GLchar* error = new GLchar[length + 1];
		glGetShaderInfoLog(shader, length, NULL, error);
		std::cerr << "LOG: " << error << std::endl;
		delete[] error;
	}
	/* return the shader ID */
	return shader;

}

GLuint Shader::LinkProgram(const GLuint vShader, const GLuint fShader)
{
	/* allocate a program */
	GLuint program;
	program = glCreateProgram();
    /* attach the vertex and fragment shaders */
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
    /* link the program */
	glLinkProgram(program);
    /* check if successful and print an error on failure */
	GLint success;
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success)
    {
		std::cout << "COMPILE FAILED" << std::endl;
	}
    /* grab the compilation log and print it */
	GLint length;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	if (length > 1)
    {
		GLchar* error = new GLchar[length + 1];
		glGetProgramInfoLog(program, length, NULL, error);
		std::cout << "LOG: " << error << std::endl;
		delete[] error;
	}
    /* clear the allocated shader resources */
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	
    /* return the program ID */
	return program;
}

GLuint Shader::BuildProgram(const std::string& vShaderFile, const std::string& fShaderFile)
{
	/* compile the vertex shader */
	GLuint vertexShader = Shader::CompileShader(vShaderFile, GL_VERTEX_SHADER);
    /* compile the fragment shader */
	GLuint fragmentShader = Shader::CompileShader(fShaderFile, GL_FRAGMENT_SHADER);
	/* link the programs and return the program ID */
	return Shader::LinkProgram(vertexShader, fragmentShader);
}

static std::string file_get_contents(const std::string& fileName)
{
    /* initialize the file object */
    std::ifstream file(fileName, std::ios::in);
    /* content will hold the contents of the loaded file */
    std::string contents;
    /* if the file existed, get the file */
    if (file.is_open())
    {
        //this string holds 1 line of the file
        std::string line;
        //get a line from the file, add a new line character and append
        while (getline(file, line))
        {
            contents += line + '\n';
        }
        file.close();
    }
    /* otherwise error */
    else
    {
        std::cerr << "Failed to read file: " << fileName << std::endl;
    }
    
    /* return the parsed string */
    return contents;
}