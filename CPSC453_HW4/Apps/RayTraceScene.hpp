#ifndef RAYTRACESCENE_H
#define RAYTRACESCENE_H

/**
file: RayTraceScene.hpp
brief: Show Ray Traced Scene
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Polygon.hpp"
#include "IFrameDispatcher.hpp"
#include "SceneParser.hpp"
#include "IInputDispatcher.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class RayTraceScene : public Polygon, public IInputListener
{
public:
    RayTraceScene(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher, const std::string& sceneFile);

    virtual void OnFrame();
    virtual void OnKey(GLint button, GLint action);

    ~RayTraceScene();

protected:

    void InitializePixels();

    void InitializeScene(const std::string& sceneFile);

    void SphereUniforms();
    void PlaneUniforms();
    void TriangleUniforms();
    void LightUniforms();
    void CameraUniforms();
    void MaterialUniforms(const Material& mat, const std::string& uniformBase);

    IFrameDispatcher*       pFrameDispatcherM;
    IInputDispatcher*       pInputDispatcherM;

    GLfloat                 fovM;
    Scene                   sceneM;

    glm::vec3               camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3               camera_dir = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3               camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat                 rightSpeed;
    GLfloat                 upSpeed;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* RAYTRACESCENE_H */