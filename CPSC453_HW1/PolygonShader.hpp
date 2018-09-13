#ifndef SYSTEM_H
#define SYSTEM_H

/**
file: system.hpp
brief: declaration of top level system driver
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Shader.h"

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

#endif /* SYSTEM_H */