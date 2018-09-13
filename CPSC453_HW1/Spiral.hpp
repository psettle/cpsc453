#pragma once
#ifndef SPIRAL_H
#define SPIRAL_H

/**
file: Square.hpp
brief: Definition of OpenGL square.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Polygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class Spiral : public Polygon
{
public:
    Spiral(IFrameDispatcher* dispatcher, GLuint numRevolutions, GLfloat maxRadius, GLuint segmentsPerRevolution, glm::vec3 const & originColor, glm::vec3 const & tipColor);

protected:
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SPIRAL_H */