/**
file: Square.cpp
brief: Definition of OpenGL square.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Square.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

Square::Square(IFrameDispatcher* dispatcher, GLdouble sideLen, GLdouble angleRad, glm::vec3 const & color, GLfloat depth)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    glm::vec4 top_left     = glm::vec4(-sideLen / 2.0f, sideLen / 2.0f, 0.0f, 0.0f);
    glm::vec4 top_right    = glm::vec4(sideLen / 2.0f, sideLen / 2.0f, 0.0f, 0.0f);
    glm::vec4 bottom_left  = glm::vec4(-sideLen / 2.0f, -sideLen / 2.0f, 0.0f, 0.0f);
    glm::vec4 bottom_right = glm::vec4(sideLen / 2.0f, -sideLen / 2.0f, 0.0f, 0.0f);

    /* Rotate vertices as requested. */
    glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 rotate_mat = glm::rotate((GLfloat)angleRad, axis);

    top_left     = top_left * rotate_mat;
    top_right    = top_right * rotate_mat;
    bottom_left  = bottom_left * rotate_mat;
    bottom_right = bottom_right * rotate_mat;

    /* Push vertices onto array to create lines. */
    vertices.push_back(glm::vec3(top_left));
    vertices.push_back(glm::vec3(top_right));

    vertices.push_back(glm::vec3(top_right));
    vertices.push_back(glm::vec3(bottom_right));

    vertices.push_back(glm::vec3(bottom_right));
    vertices.push_back(glm::vec3(bottom_left));

    vertices.push_back(glm::vec3(bottom_left));
    vertices.push_back(glm::vec3(top_left));

    for (uint32 i = 0; i < vertices.size(); ++i)
    {
        colors.push_back(color);
    }

    Configure(dispatcher, vertices, colors, glm::vec3(0.0f, 0.0f, depth), GL_LINES);
}