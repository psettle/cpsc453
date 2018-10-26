#ifndef BEZIERCONTROLLINES_H
#define BEZIERCONTROLLINES_H

/**
file: BezierQuad.hpp
brief:.
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

class BezierControlLines : public Polygon
{
public:
    BezierControlLines(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, GLfloat scale);

    BezierControlLines(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, glm::vec3& P3, GLfloat scale);
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* BEZIERCONTROLLINES_H */