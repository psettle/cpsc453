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

enum ActiveShaderEnum;

class Image : public IFrameListener
{
public:
    Image(std::string const & imagePath, IFrameDispatcher* dispatcher);

    void Translate(glm::vec3 direction);

    void Scale(GLfloat scaleFactor);

    void Rotate(GLfloat rotationAngle);

    void IncrementShader();

    void DecrementShader();

    void SetGaussianFilterSize(GLint size);

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