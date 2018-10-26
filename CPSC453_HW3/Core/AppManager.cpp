/**
file: AppManager.cpp
brief: Top level app manager for cpsc453 HW1
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "AppManager.hpp"
#include "BezierQuadApp.hpp"
#include "BezierCubeApp.hpp"
#include "NameApp.hpp"
#include "StarWarsApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

AppManager::AppManager(IFrameDispatcher* dispatcher, IInputPoller* poller)
    : pFrameDispatcherM(dispatcher), pInputPollerM(poller)
{
    pFrameDispatcherM->RegisterFrameListener(this);
    SetCurrentApp();
}

void AppManager::OnFrame()
{
    ProcessAppSelectionInput();
}

void AppManager::ProcessAppSelectionInput()
{
    KeyStateEnum up_state = pInputPollerM->GetKey(GLFW_KEY_UP);
    KeyStateEnum down_state = pInputPollerM->GetKey(GLFW_KEY_DOWN);

    if (up_state != upKeyCurrentStateM)
    {
        if (up_state == KEY_STATE_RELEASE)
        {
            IncrementActiveApp();
        }

        upKeyCurrentStateM = up_state;
    }

    if (down_state != downKeyCurrentStateM)
    {
        if (down_state == KEY_STATE_RELEASE)
        {
            DecrementActiveApp();
        }

        downKeyCurrentStateM = down_state;
    }
}

void AppManager::IncrementActiveApp()
{
    switch (activeAppEnumM)
    {
    case ACTIVE_APP_BEZIER_QUAD:
        activeAppEnumM = ACTIVE_APP_BEZIER_CUBE;
        break;
    case ACTIVE_APP_BEZIER_CUBE:
        activeAppEnumM = ACTIVE_APP_NAME;
        break;
    case ACTIVE_APP_NAME:
        activeAppEnumM = ACTIVE_APP_STARWARS;
        break;
    case ACTIVE_APP_STARWARS:
        activeAppEnumM = ACTIVE_APP_BEZIER_QUAD;
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
    case ACTIVE_APP_BEZIER_QUAD:
        activeAppEnumM = ACTIVE_APP_STARWARS;
        break;
    case ACTIVE_APP_BEZIER_CUBE:
        activeAppEnumM = ACTIVE_APP_BEZIER_QUAD;
        break;
    case ACTIVE_APP_NAME:
        activeAppEnumM = ACTIVE_APP_BEZIER_CUBE;
        break;
    case ACTIVE_APP_STARWARS:
        activeAppEnumM = ACTIVE_APP_NAME;
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
    case ACTIVE_APP_BEZIER_QUAD:
        pActiveAppM = new BezierQuadApp(pFrameDispatcherM);
        break;
    case ACTIVE_APP_BEZIER_CUBE:
        pActiveAppM = new BezierCubeApp(pFrameDispatcherM);
        break;
    case ACTIVE_APP_NAME:
        pActiveAppM = new NameApp(pFrameDispatcherM, pInputPollerM, "Patrick");
        break;
    case ACTIVE_APP_STARWARS:
        pActiveAppM = new StarWarsApp(pFrameDispatcherM, pInputPollerM);
        break;
    default:
      break;
    }
}

AppManager::~AppManager()
{
    delete pActiveAppM;
    pFrameDispatcherM->UnregisterFrameListener(this);
}
