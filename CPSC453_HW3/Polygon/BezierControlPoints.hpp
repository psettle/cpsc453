#ifndef BEZIERCONTROLPOINTS_H
#define BEZIERCONTROLPOINTS_H

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

class BezierControlPoints : public Polygon
{
public:
    BezierControlPoints(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, GLfloat scale);

    BezierControlPoints(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, glm::vec3& P3, GLfloat scale);

    virtual void OnFrame();
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* BEZIERCONTROLPOINTS_H */