#ifndef RAYTRACEAPP_H
#define RAYTRACEAPP_H

/**
file: RayTraceApp.hpp
brief: Show Ray Traced Scenes
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IApp.hpp"
#include "IFrameDispatcher.hpp"
#include "IInputDispatcher.hpp"
#include "RayTraceScene.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/



class RayTraceApp : public IApp
{
public:
    RayTraceApp(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher);

    ~RayTraceApp();

    void OnKey(GLint key, GLint action);

protected:

    void SetScene(GLuint sceneID);

    RayTraceScene*          pSceneM = nullptr;

    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    IInputDispatcher*       pInputDispatcherM = nullptr;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* RAYTRACEAPP_H */