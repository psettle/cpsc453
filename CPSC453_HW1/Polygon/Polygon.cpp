/**
file: Polygon.cpp
brief: A collection of OpenGL Triangles with a color.
notes:
    Very loosly based off of:
    https://github.com/psettle/CrappyChess/blob/master/GlObject.cpp

    (My own hobby code)
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

/**********************************************************
                       DEFINITIONS
**********************************************************/

void Polygon::Configure
    (
    IFrameDispatcher* dispatcher,
    std::vector<glm::vec3> const & vertices,
    std::vector<glm::vec3> const & colors,
    glm::vec3 const & postition,
    GLuint glDrawMode
    )
{
    GLuint vertex_buffer_object;
    GLuint color_buffer_object;

    /* Add position to vertices. */
    std::vector<glm::vec3> vertices_copy = vertices;

    for (uint32 i = 0; i < vertices_copy.size(); ++i)
    {
        vertices_copy[i] += postition;
    }
    
    /* generate a vertex array and buffers for each array we need to pass */
    glGenVertexArrays(1, &vertexArrayHandleM);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &color_buffer_object);
    
    /* add all the new buffers to the list of buffers to delete */
    buffersToFreeM.push_back(color_buffer_object);
    buffersToFreeM.push_back(vertex_buffer_object);

    /* set the vertex array to bind to */
    glBindVertexArray(vertexArrayHandleM);

    /* bind an array buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    /* load the points into the buffer */
    glBufferData(GL_ARRAY_BUFFER, vertices_copy.size() * sizeof(glm::vec3), &vertices_copy[0], GL_STATIC_DRAW);
    /* tell openGL what kind of data we passed */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    /* bind the buffer to the vertex array object (at index 0)*/
    glEnableVertexAttribArray(0);

    vertexCountM = vertices.size() * 3;

    /* Bind color buffer */
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    /* clear the vertex array object */
    glBindVertexArray(0);
    /* clear the array buffer */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Create shader for the class, if it doesn't exist */
    if (nullptr == Polygon::shader)
    {
        /* TODO: this is never deleted, could be deleted on system deinit, or when no polygons exist. */
        Polygon::shader = new PolygonShader();
    }

    glDrawModeM = glDrawMode;

    /* Mark object as configured. */
    isConfiguredM = true;
    pFrameDispatcherM = dispatcher;
    pFrameDispatcherM->RegisterFrameListener(this);
}

void Polygon::OnFrame()
{
    if (!isConfiguredM)
    {
        std::cerr << "Frame callback on unconfigured polygon" << std::endl;
        return;
    }

    Polygon::shader->Enable();
   
    /* set the vertex array object active */
    glBindVertexArray(vertexArrayHandleM);
    /* draw the elements */
    glDrawArrays(glDrawModeM, 0, vertexCountM);
    /* clear the array object */
    glBindVertexArray(0);

    Polygon::shader->Disable();
}

Polygon::~Polygon()
{
    pFrameDispatcherM->UnregisterFrameListener(this);
    glDeleteBuffers(buffersToFreeM.size(), &buffersToFreeM[0]);
    glDeleteVertexArrays(1, &vertexArrayHandleM);
}

Shader* Polygon::shader = nullptr;