/**
file: EquilateralTriangle.cpp
brief: Definition of OpenGL EquilateralTriangle.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "EquilateralTriangle.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const GLfloat ROOT_3 = sqrt(3.0f);

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

EquilateralTriangle::EquilateralTriangle(IFrameDispatcher* dispatcher, GLdouble sideLen, glm::vec3 const & color, glm::vec3 const & position)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    glm::vec3 top = glm::vec3(0.0f, sideLen / ROOT_3, 0.0f);
    glm::vec3 left = glm::vec3(-sideLen / 2.0f, -sideLen / (ROOT_3 * 2.0f), 0.0f);
    glm::vec3 right = glm::vec3(sideLen / 2.0f, -sideLen / (ROOT_3 * 2.0f), 0.0f);

    /* Push vertices onto array to create triangle. */
    vertices.push_back(top);
    vertices.push_back(left);
    vertices.push_back(right);

    /* Populate colours */
    for (uint32 i = 0; i < vertices.size(); ++i)
    {
        colors.push_back(color);
    }

    Configure(dispatcher, vertices, colors, position, GL_TRIANGLES);
}