#ifndef IMAGE_H
#define IMAGE_H

/**
file: Image.hpp
brief: Shows an openGL 2D image.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Common.hpp"
#include "IFrameListener.hpp"
#include "IFrameDispatcher.hpp"
#include "Shader.hpp"
#include "StbImage.hpp"
#include "Texture.hpp"
#include "RenderPipeline.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

enum ActiveShaderEnum
{
    ACTIVE_SHADER_PLAIN,
    ACTIVE_SHADER_GREY_1,
    ACTIVE_SHADER_GREY_2,
    ACTIVE_SHADER_GREY_3,
    ACTIVE_SHADER_SEPIA,
    ACTIVE_SHADER_HALLOWEEN, /* Switched the R & G values, makes things look orange & green kinda. */
    ACTIVE_SHADER_VERTICAL_SOBEL,
    ACTIVE_SHADER_HORIZONTAL_SOBEL,
    ACTIVE_SHADER_UNSHARP_MASK,
    ACTIVE_SHADER_GAUSSIAN_3x3,
    ACTIVE_SHADER_GAUSSIAN_5x5,
    ACTIVE_SHADER_GAUSSIAN_7x7,
    ACTIVE_SHADER_GAUSSIAN_NxN,

    ACTIVE_SHADER_COUNT,
    ACTIVE_SHADER_DEFAULT = ACTIVE_SHADER_PLAIN,
    ACTIVE_SHADER_COUNT_RESOLUTION_REQUIRED_LINE = ACTIVE_SHADER_VERTICAL_SOBEL
};

class Image : public IFrameListener
{
public:
    Image(std::string const & imagePath, IFrameDispatcher* dispatcher);

    void Translate(glm::vec3 direction);

    void Scale(GLfloat scaleFactor);

    void Rotate(GLfloat rotationAngle);

    void IncrementShader();

    void DecrementShader();

    bool SetGaussianFilterSize(GLint size);

    virtual void OnFrame();

    virtual ~Image();
protected:

    void SetShader();

    void RawScale(GLfloat scaleFactor);
    void RawRotate(GLfloat rotationAngle);

    std::vector<glm::vec3> GetInitialVertices() const;
    std::vector<glm::vec2> GetInitialUVs() const;
    std::vector<GLfloat> GetGaussianFilter(GLint width) const;

    GLuint vertexCountM = 0;
    GLuint vertexArrayHandleM = 0;
    std::vector<GLuint> buffersToFreeM;

    IFrameDispatcher* pFrameDispatcherM = nullptr;

    Shader*               pShaderM = nullptr;
    std::vector<Shader*>  shaderQueueM;
    ActiveShaderEnum    activeShaderM;

    StbImage* stbImageM = nullptr;
    Texture* pTextureM = nullptr;

    RenderPipeline renderPipelineM;

    glm::mat4 modelMatrixM = glm::mat4(1.0f);
    GLfloat currentScaleM = 1.0f;
    glm::vec3 currentPosM = glm::vec3(0.0f);
    GLfloat currentRotationM = 0.0f;

    std::vector<float> gaussianFilter;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* POLYGON_H */
