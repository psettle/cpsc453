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
#include "Texture.hpp"

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
        std::vector<glm::vec2> const & uvs,
        Texture* pTexture
        );

    virtual void OnFrame();

    virtual void SetUniforms() = 0;

    virtual ~Polygon();
protected:

    GLuint vertexArrayHandleM = 0;
    GLuint vertexCountM = 0;
    GLuint glDrawModeM = GL_LINES;
    std::vector<GLuint> buffersToFreeM;

    bool isConfiguredM = false;
    IFrameDispatcher* pFrameDispatcherM = nullptr;

    Texture*    pTextureM = nullptr;

    static Shader* shader;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* POLYGON_H */