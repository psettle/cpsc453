#ifndef BEZIERSHADERQUAD_H
#define BEZIERSHADERQUAD_H

/**
file: BezierShaderQuad.hpp
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

class BezierShaderQuad : public Shader
{
public:
    BezierShaderQuad() : Shader("shaders/PolygonVertex.glsl", "shaders/PolygonFragment.glsl", "shaders/BezierGeometryQuad.glsl") {}
};

#endif /* BEZIERSHADERQUAD_H */