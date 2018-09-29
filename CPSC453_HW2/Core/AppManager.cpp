/**
file: AppManager.cpp
brief: Top level app manager for cpsc453 HW1
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include <sstream> 

#include "AppManager.hpp"
#include "ImagesApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

enum ActiveAppEnum
{
    ACTIVE_APP_IMAGES,

    ACTIVE_APP_COUNT,
    ACTIVE_APP_DEFAULT = ACTIVE_APP_IMAGES
};

AppManager::AppManager(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher)
    : pFrameDispatcherM(frameDispatcher), pInputDispatcherM(inputDispatcher)
{
    pFrameDispatcherM->RegisterFrameListener(this);
    pInputDispatcherM->RegisterInputListener(this);
    SetCurrentApp();
}

void AppManager::OnFrame()
{

}

void AppManager::OnKey(GLint key, GLint action)
{
    /* All done in one app, so hijacking these keys for controlling gaussian filter degree */
    //if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
    //{
    //    IncrementActiveApp();
    //}

    //if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
    //{
    //    DecrementActiveApp();
    //}
}

void AppManager::IncrementActiveApp()
{
    switch (activeAppEnumM)
    {
    case ACTIVE_APP_IMAGES:
        activeAppEnumM = ACTIVE_APP_IMAGES;
        break;
    default:
        break;
    }
    
    SetCurrentApp();
}
void AppManager::DecrementActiveApp()
{
    switch (activeAppEnumM)
    {
    case ACTIVE_APP_IMAGES:
        activeAppEnumM = ACTIVE_APP_IMAGES;
        break;
    default:
        break;
    }

    SetCurrentApp();
}

void AppManager::SetCurrentApp()
{
    delete pActiveAppM;

    switch (activeAppEnumM)
    {
    case ACTIVE_APP_IMAGES:
        pActiveAppM = new ImagesApp(pFrameDispatcherM, pInputDispatcherM);
        break;
    default:
        break;
    }
}

AppManager::~AppManager()
{
    delete pActiveAppM;
    pFrameDispatcherM->UnregisterFrameListener(this);
    pInputDispatcherM->UnregisterInputListener(this);
}