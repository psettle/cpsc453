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
#include "OrreryApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

AppManager::AppManager(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher)
    : pFrameDispatcherM(frameDispatcher), pInputDispatcherM(inputDispatcher), activeAppEnumM(ACTIVE_APP_ORRERY)
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

}

void AppManager::IncrementActiveApp()
{
    switch (activeAppEnumM)
    {
    case ACTIVE_APP_ORRERY:
        activeAppEnumM = ACTIVE_APP_ORRERY;
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
    case ACTIVE_APP_ORRERY:
        activeAppEnumM = ACTIVE_APP_ORRERY;
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
    case ACTIVE_APP_ORRERY:
        pActiveAppM = new OrreryApp(pFrameDispatcherM, pInputDispatcherM);
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
