#ifndef ORRERYAPP_H
#define ORRERYAPP_H

/**
file: OrreryApp.hpp
brief: An app that shows the solar system
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IApp.hpp"
#include "IFrameDispatcher.hpp"
#include "IInputDispatcher.hpp"
#include "Polygon.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "SceneGraph.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class OrreryApp : public IApp
{
public:
    OrreryApp(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher);

    ~OrreryApp();

    void OnFrame();

    void OnKey(GLint key, GLint action);

    void OnScroll(GLdouble scroll);

    void OnMouseMove(GLdouble xpos, GLdouble ypos);

    void OnMouseButton(GLint button, GLint action);

protected:

    void SimulateTime(GLfloat dt);

    glm::vec3 CalculateOrbitalPosition(GLfloat elapsedTime, GLfloat radius, GLfloat inclination, GLfloat period) const;

    void ConstructScene();

    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    IInputDispatcher*       pInputDispatcherM = nullptr;
    Camera*                 pCameraM = nullptr;
    Sphere*                 pSunM = nullptr;
    Sphere*                 pEarthM = nullptr;
    Sphere*                 pMoonM = nullptr;
    Sphere*                 pMarsM = nullptr;
    Sphere*                 pStarsM = nullptr;

    SceneGraph              sceneGraphM;


    GLfloat                 speedM = 0.5f;
    bool                    isPausedM = false;
    GLfloat                 prevTime = -1.0f;
    GLfloat                 elapsedTime = 0.0f;

    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* ORRERYAPP_H */