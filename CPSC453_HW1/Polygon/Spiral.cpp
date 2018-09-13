/**
file: Spiral.cpp
brief: Definition of OpenGL Spiral.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Spiral.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

Spiral::Spiral(IFrameDispatcher* dispatcher, GLuint numRevolutions, GLfloat maxRadius, GLuint segmentsPerRevolution, glm::vec3 const & originColor, glm::vec3 const & tipColor)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    GLuint segmentCount = segmentsPerRevolution * numRevolutions;

    glm::vec3 colorRange = tipColor - originColor;

    for (uint32 i = 0; i < segmentCount; i++)
    {
        GLfloat startAngle = 2 * PI * ( i % segmentsPerRevolution) / (GLfloat)segmentsPerRevolution;
        GLfloat endAngle = 2 * PI * ( (i + 1) % segmentsPerRevolution) / (GLfloat)segmentsPerRevolution;

        GLfloat startRadius = maxRadius * (i / (GLfloat)segmentCount);
        GLfloat endRadius = maxRadius * ((i + 1) / (GLfloat)segmentCount);

        glm::vec3 colorStart = (i / (GLfloat)segmentCount) * colorRange + originColor;
        glm::vec3 colorEnd = ((i + 1) / (GLfloat)segmentCount) * colorRange + originColor;

        glm::vec3 lineStart;
        glm::vec3 lineEnd;

        lineStart.x = startRadius * glm::cos(startAngle);
        lineStart.y = startRadius * glm::sin(startAngle);
        lineStart.z = 0.0f;

        lineEnd.x = endRadius * glm::cos(endAngle);
        lineEnd.y = endRadius * glm::sin(endAngle);
        lineEnd.z = 0.0f;

        vertices.push_back(lineStart);
        vertices.push_back(lineEnd);

        colors.push_back(colorStart);
        colors.push_back(colorEnd);
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f, 0.0f, 0.0f), GL_LINES);
}