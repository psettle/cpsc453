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

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class Image : public IFrameListener
{
public:
    Image(std::string const & imagePath, IFrameDispatcher* dispatcher);

    void Translate(glm::vec3 direction);

    void Scale(GLfloat scaleFactor);

    void Rotate(GLfloat rotationAngle);

    virtual void OnFrame();

    virtual ~Image();
protected:

    void RawScale(GLfloat scaleFactor);
    void RawRotate(GLfloat rotationAngle);

    std::vector<glm::vec3> GetInitialVertices() const;
    std::vector<glm::vec2> GetInitialUVs() const;

    GLuint vertexArrayHandleM = 0;
    GLuint vertexCountM = 0;
    std::vector<GLuint> buffersToFreeM;

    IFrameDispatcher* pFrameDispatcherM = nullptr;
    static Shader* shader;
    StbImage* stbImageM = nullptr;
    Texture* pTextureM = nullptr;

    glm::mat4 modelMatrixM = glm::mat4(1.0f);
    GLfloat currentScaleM = 1.0f;
    glm::vec3 currentPos = glm::vec3(0.0f);
    GLfloat currentRotationM = 0.0f;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* POLYGON_H */