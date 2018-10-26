/**
file: BezierQuad.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "BezierControlPoints.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

BezierControlPoints::BezierControlPoints(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, GLfloat scale)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.clear();
    colors.clear();

    vertices.push_back(P0);
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

    vertices.push_back(P1);
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

    vertices.push_back(P2);
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

    for (auto& point : vertices)
    {
        point *= scale;
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_POINTS);
}

BezierControlPoints::BezierControlPoints(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, glm::vec3& P3, GLfloat scale)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.push_back(P0);
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

    vertices.push_back(P1);
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

    vertices.push_back(P2);
    colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

    vertices.push_back(P3);
    colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

    for (auto& point : vertices)
    {
        point *= scale;
    }
    
    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_POINTS);
}

void BezierControlPoints::OnFrame()
{
    //kinda hacky, but override the point size for this object type, then set it back so it doesn't affect other objects
    glPointSize(5.0f);
    Polygon::OnFrame();
    glPointSize(1.0f);
}