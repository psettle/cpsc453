#ifndef POLYGON_H
#define POLYGON_H

/**
file: Polygon.hpp
brief: A collection of OpenGL Triangles with a color.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Common.hpp"
#include "IFrameListener.hpp"
#include "IFrameDispatcher.hpp"
#include "PolygonShader.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class Polygon : public IFrameListener
{
public:
    void Configure
        (
        IFrameDispatcher* dispatcher,
        std::vector<glm::vec3> const & vertices,
        std::vector<glm::vec3> const & colors,
        glm::vec3 const & postition,
        GLuint glDrawMode,
        Shader* shaderIn = nullptr /* Not deleted if provided, caller is responsable. */
        );

    virtual void OnFrame();

    virtual void ApplyTranslation(const glm::vec3& translation);

    virtual ~Polygon();
protected:

private:
    GLuint vertexArrayHandleM = 0;
    GLuint vertexCountM = 0;
    GLuint glDrawModeM = GL_LINES;
    std::vector<GLuint> buffersToFreeM;
    Shader* pShaderM;

    glm::mat4 translationMatrix;

    bool isConfiguredM = false;
    IFrameDispatcher* pFrameDispatcherM = nullptr;


    static Shader* shader;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* POLYGON_H */