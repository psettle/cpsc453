/**
file: RenderPipeline.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "RenderPipeline.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

const static std::vector<glm::vec3> vertices =
{
    glm::vec3(-1.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 0.0f),

    glm::vec3(1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, 1.0f, 0.0f)
};

const static std::vector<glm::vec2> uvs =
{
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),

    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f)
};

const static GLuint vertexCount = vertices.size();

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

RenderPipeline::RenderPipeline()
{
    /* Make a temp textures object to hold partial renderings */
    frameTextureAM = new Texture(WINDOW_WIDTH, WINDOW_HEIGHT);
    frameTextureBM = new Texture(WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Create frame buffers and bind the textures to them. */
    frameTextureAM->Enable();
    glGenFramebuffers(1, &frameBufferAM);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferAM);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTextureAM->GetTextureHandle(), 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    frameTextureAM->Disable();

    frameTextureBM->Enable();
    glGenFramebuffers(1, &frameBufferBM);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferBM);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTextureBM->GetTextureHandle(), 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    frameTextureBM->Disable();

    /* Generate a normalized vector/UV set to render the image with */
    GLuint vertex_buffer_object;
    GLuint uv_buffer_object;

    glGenVertexArrays(1, &frameBufferVertexArrayM);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &uv_buffer_object);

    buffersToFreeM.push_back(vertex_buffer_object);
    buffersToFreeM.push_back(uv_buffer_object);

    glBindVertexArray(frameBufferVertexArrayM);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderPipeline::ClearPipe()
{
    targetFrameBufferToggle = false;
}

void RenderPipeline::StartRender(Texture* texture, Shader* shader)
{
    pShaderM = shader;
    pTextureM = texture;

    pShaderM->Enable();
    pTextureM->Enable();
}

/* Returns result of render, if isFinalRender != true */
Texture* RenderPipeline::EndRender(bool isFinalRender = false, GLuint vertexArrayObject = 0, GLuint vertexCountArg = vertexCount)
{
    if (isFinalRender)
    {
        /* Reset to default framebuffer, draw to provided vertxt array */
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindVertexArray(vertexArrayObject);
    }
    else
    {
        if (targetFrameBufferToggle)
        {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferAM);
            pTextureM = frameTextureAM;
        }
        else
        {
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferBM);
            pTextureM = frameTextureBM;
        }

        targetFrameBufferToggle = !targetFrameBufferToggle;
        glBindVertexArray(frameBufferVertexArrayM);
    }
    
    glDrawArrays(GL_TRIANGLES, 0, vertexCountArg);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    pShaderM->Disable();
    pTextureM->Disable();

    return pTextureM;
}

RenderPipeline::~RenderPipeline()
{
    delete frameTextureAM;
    delete frameTextureBM;
    glDeleteBuffers(buffersToFreeM.size(), &buffersToFreeM[0]);
    glDeleteVertexArrays(1, &frameBufferVertexArrayM);
    glDeleteFramebuffers(1, &frameBufferAM);
    glDeleteFramebuffers(1, &frameBufferBM);
}