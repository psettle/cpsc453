#ifndef RENDERPIPELINE_H
#define RENDERPIPELINE_H

/**
file: RenderPipeline.hpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Texture.hpp"
#include "Shader.hpp"
#include "Common.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/
class RenderPipeline
{
public:

    RenderPipeline();

    void ClearPipe();

    void StartRender(Texture* texture, Shader* shader);

    /* Returns result of render, if isFinalRender != true */
    Texture* EndRender(bool isFinalRender, GLuint vertexArrayObject, GLuint vertexCount);

    ~RenderPipeline();

protected:

    GLuint frameBufferAM;
    Texture* frameTextureAM;
    GLuint frameBufferBM;
    Texture* frameTextureBM;
    GLuint frameBufferVertexArrayM;

    Shader* pShaderM = nullptr;
    Texture* pTextureM = nullptr;

    bool targetFrameBufferToggle = false;

    std::vector<GLuint> buffersToFreeM;
};
/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* RENDERPIPELINE_H */