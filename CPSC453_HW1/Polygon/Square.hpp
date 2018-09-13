#ifndef SQUARE_H
#define SQUARE_H

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

class Square : public Polygon
{
public:
    Square(IFrameDispatcher* dispatcher, GLdouble sideLen, GLdouble angleRad, glm::vec3 const & color, GLfloat depth);

protected:
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SQUARE_H */