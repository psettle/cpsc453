/**
file: RayTraceApp.cpp
brief: Show Ray Traced Scenes
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "RayTraceApp.hpp"
#include "RayTraceScene.hpp"
#include "SceneParser.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

constexpr auto DEFAULT_SCENE = 0;

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/



static const std::vector<std::string> sceneFiles = {
    "scenes/scene1.txt",
    "scenes/scene2.txt",
    "scenes/scene3.txt"
};

RayTraceApp::RayTraceApp(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher)
    : pFrameDispatcherM(frameDispatcher), pInputDispatcherM(inputDispatcher)
{
    pInputDispatcherM->RegisterInputListener(this);
    SetScene(DEFAULT_SCENE);
}

RayTraceApp::~RayTraceApp()
{
    delete pSceneM;
    pInputDispatcherM->UnregisterInputListener(this);
}

void RayTraceApp::OnKey(GLint key, GLint action)
{
    if (action != GLFW_RELEASE && action != GLFW_REPEAT)
    {
        return;
    }

    switch (key)
    {
    case GLFW_KEY_1:
    case GLFW_KEY_2:
    case GLFW_KEY_3:
        SetScene(key - GLFW_KEY_1);
        break;
    default:
        break;
    }
}

void RayTraceApp::SetScene(GLuint sceneID)
{
    if (nullptr != pSceneM)
    {
        delete pSceneM;
    }

    pSceneM = new RayTraceScene(pFrameDispatcherM, pInputDispatcherM, sceneFiles[sceneID]);
}

