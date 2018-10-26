/**
file: BezierQuad.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "BezierControlLines.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

BezierControlLines::BezierControlLines(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, GLfloat scale)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.push_back(P0);
    vertices.push_back(P1);
    colors.push_back(glm::vec3(0.7f));
    colors.push_back(glm::vec3(0.7f));

    vertices.push_back(P1);
    vertices.push_back(P2);
    colors.push_back(glm::vec3(0.7f));
    colors.push_back(glm::vec3(0.7f));

    for (auto& point : vertices)
    {
        point *= scale;
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_LINES);
}

BezierControlLines::BezierControlLines(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, glm::vec3& P3, GLfloat scale)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.push_back(P0);
    vertices.push_back(P1);
    colors.push_back(glm::vec3(0.5f));
    colors.push_back(glm::vec3(0.5f));

    vertices.push_back(P1);
    vertices.push_back(P2);
    colors.push_back(glm::vec3(0.5f));
    colors.push_back(glm::vec3(0.5f));

    vertices.push_back(P2);
    vertices.push_back(P3);
    colors.push_back(glm::vec3(0.5f));
    colors.push_back(glm::vec3(0.5f));

    for (auto& point : vertices)
    {
        point *= scale;
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_LINES);
}