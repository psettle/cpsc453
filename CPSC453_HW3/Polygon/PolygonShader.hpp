#ifndef POLYGONSHADER_H
#define POLYGONSHADER_H

/**
file: system.hpp
brief: declaration of top level system driver
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Shader.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

class PolygonShader : public Shader
{
public:
    PolygonShader() : Shader("shaders/PolygonVertex.glsl", "shaders/PolygonFragment.glsl") {}
};

#endif /* POLYGONSHADER_H */