#ifndef BEZIER_H
#define BEZIER_H

/**
file: Bezier.hpp
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

class Bezier : public Polygon
{
public:

    Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, GLfloat scale, glm::vec3 offset = glm::vec3(0.0f));

    Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, GLfloat scale, glm::vec3 offset = glm::vec3(0.0f));

    Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, GLfloat scale, glm::vec3 offset = glm::vec3(0.0f));

    Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, glm::vec3& P3, GLfloat scale, glm::vec3 offset = glm::vec3(0.0f));

protected:
    static Shader* quadShader;
    static Shader* cubeShader;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* BEZIER_H */