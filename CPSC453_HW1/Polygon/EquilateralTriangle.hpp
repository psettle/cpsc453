#ifndef EQUILATERALTRIANGLE_H
#define EQUILATERALTRIANGLE_H

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

class EquilateralTriangle : public Polygon
{
public:
    EquilateralTriangle(IFrameDispatcher* dispatcher, GLdouble sideLen, glm::vec3 const & color, glm::vec3 const & position);

protected:
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* EQUILATERALTRIANGLE_H */