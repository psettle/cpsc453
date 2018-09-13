#ifndef CIRCLE_H
#define CIRCLE_H

/**
file: Circle.hpp
brief: Definition of OpenGL Circle.
notes:
    Not technically a part of any apps, mostly proof of concept for curves.
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

class Circle : public Polygon
{
public:
    Circle(IFrameDispatcher* dispatcher, GLfloat radius, GLuint segmentCount, glm::vec3 const & color, GLfloat depth);

protected:
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* CIRCLE_H */