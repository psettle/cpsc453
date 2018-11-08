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

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class RayTraceScene : public Polygon
{
public:
    RayTraceScene(IFrameDispatcher* frameDispatcher, const std::string& sceneFile);

    virtual void OnFrame();

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

    GLfloat                 fovM;
    Scene                   sceneM;

    glm::vec3               camera_pos = glm::vec3(0.0f);
    glm::vec3               camera_dir = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3               camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

    IFrameDispatcher*       pFrameDispatcherM = nullptr;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* RAYTRACESCENE_H */