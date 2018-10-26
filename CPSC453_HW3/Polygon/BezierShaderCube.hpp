#ifndef BEZIERSHADERCUBE_H
#define BEZIERSHADERCUBE_H

/**
file: BezierShaderCube.hpp
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

class BezierShaderCube : public Shader
{
public:
    BezierShaderCube() : Shader("shaders/PolygonVertex.glsl", "shaders/PolygonFragment.glsl", "shaders/BezierGeometryCube.glsl") {}
};

#endif /* BEZIERSHADERCUBE_H */