/**
file: Bezier.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Bezier.hpp"
#include "BezierShaderQuad.hpp"
#include "BezierShaderCube.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

Bezier::Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, GLfloat scale, glm::vec3 offset)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.push_back((P0 + offset) * scale);
    colors.push_back(glm::vec3(0.0f));

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_POINT);
}

Bezier::Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, GLfloat scale, glm::vec3 offset)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.push_back((P0 + offset) * scale);
    vertices.push_back((P1 + offset) * scale);
    colors.push_back(glm::vec3(0.0f));
    colors.push_back(glm::vec3(0.0f));

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_LINES);
}

Bezier::Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, GLfloat scale, glm::vec3 offset)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.push_back((P0 + offset) * scale);
    vertices.push_back((P1 + offset) * scale);
    vertices.push_back((P2 + offset) * scale);
    vertices.push_back(glm::vec3(0.0f)); //filler point, openGL expects 4 points
    colors.push_back(glm::vec3(0.0f));
    colors.push_back(glm::vec3(0.0f));
    colors.push_back(glm::vec3(0.0f));
    colors.push_back(glm::vec3(0.0f));

    /* Create shader for the class, if it doesn't exist */
    if (nullptr == Bezier::quadShader)
    {
        /* TODO: this is never deleted, could be deleted on system deinit, or when no polygons exist. */
        Bezier::quadShader = new BezierShaderQuad();
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_LINES_ADJACENCY, Bezier::quadShader);
}

Bezier::Bezier(IFrameDispatcher* dispatcher, glm::vec3& P0, glm::vec3& P1, glm::vec3& P2, glm::vec3& P3, GLfloat scale, glm::vec3 offset)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    vertices.push_back((P0 + offset) * scale);
    vertices.push_back((P1 + offset) * scale);
    vertices.push_back((P2 + offset) * scale);
    vertices.push_back((P3 + offset) * scale);
    colors.push_back(glm::vec3(0.0f));
    colors.push_back(glm::vec3(0.0f));
    colors.push_back(glm::vec3(0.0f));
    colors.push_back(glm::vec3(0.0f));

    if (nullptr == Bezier::cubeShader)
    {
        /* TODO: this is never deleted, could be deleted on system deinit, or when no polygons exist. */
        Bezier::cubeShader = new BezierShaderCube();
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f), GL_LINES_ADJACENCY, Bezier::cubeShader);
}

Shader* Bezier::quadShader = nullptr;
Shader* Bezier::cubeShader = nullptr;