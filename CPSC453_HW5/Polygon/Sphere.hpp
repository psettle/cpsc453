#ifndef SPHERE_H
#define SPHERE_H

/**
file: Sphere.hpp
brief: Definition of OpenGL Sphere.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Polygon.hpp"
#include "Camera.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class Sphere : public Polygon
{
public:
    Sphere(IFrameDispatcher* dispatcher, Camera* pCamera, GLfloat radius, std::string const & textureFilename, GLfloat ambient, GLfloat diffuse);

    void AddSceneReference(glm::mat4* reference);

    virtual void SetUniforms();
protected:

    glm::vec3 SphericalToCartesian(GLfloat theta, GLfloat phi, GLfloat radius) const;

    std::vector<glm::mat4*>  sceneQueueM;

    Camera* pCameraM;

    GLfloat ambientM = 1.0f;
    GLfloat diffuseM = 0.0f;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SPHERE_H */