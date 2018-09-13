/**
file: Circle.cpp
brief: Definition of OpenGL Circle.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Circle.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

Circle::Circle(IFrameDispatcher* dispatcher, GLdouble radius, GLuint segmentCount, glm::vec3 const & color, GLfloat depth)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    for (uint32 i = 0; i < segmentCount; ++i)
    {
        glm::vec3 lineStart;
        glm::vec3 lineEnd;

        lineStart.x = radius * glm::cos(2 * PI_D * i / segmentCount);
        lineStart.y = radius * glm::sin(2 * PI_D * i / segmentCount);
        lineStart.z = 0.0f;

        lineEnd.x = radius * glm::cos(2 * PI_D * ( i + 1 ) / segmentCount);
        lineEnd.y = radius * glm::sin(2 * PI_D * ( i + 1 ) / segmentCount);
        lineEnd.z = 0.0f;

        vertices.push_back(lineStart);
        vertices.push_back(lineEnd);
    }

    for (uint32 i = 0; i < vertices.size(); ++i)
    {
        colors.push_back(color);
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f, 0.0f, depth), GL_LINES);
}