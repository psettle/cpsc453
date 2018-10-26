#ifndef APPMANAGER_H
#define APPMANAGER_H

/**
file: AppManager.hpp
brief: Top level app manager for cpsc453 HW1
notes:
    - Creates and deletes apps (each app is a "part" of the assignment")
    - Processes and passes keyboard input to apps
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Common.hpp"
#include "IFrameDispatcher.hpp"
#include "IFrameListener.hpp"
#include "IInputPoller.hpp"
#include "IApp.hpp"

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
    ACTIVE_APP_BEZIER_QUAD,
    ACTIVE_APP_BEZIER_CUBE,
    ACTIVE_APP_NAME,
    ACTIVE_APP_STARWARS,

    ACTIVE_APP_COUNT,
    ACTIVE_APP_DEFAULT = ACTIVE_APP_STARWARS
};

class AppManager: public IFrameListener
{
public:
    /**
        Initialize the appmanager and boot the default app
     */
    AppManager(IFrameDispatcher* dispatcher, IInputPoller* poller);

    /**
        Called on each frame if registed to a frame dispatcher
     */
    virtual void OnFrame();

    /**
        Teardown the current app.
     */
    ~AppManager();
protected:

    /**
        Detects up and down arrow key release events, and then calls increment or decrement app.
     */
    void ProcessAppSelectionInput();

    /**
        Increment activeAppEnumM to the next valid app, rolling over as required.
     */
    void IncrementActiveApp();

    /**
        Decrement activeAppEnumM to the previous valid app, rolling under as required.
    */
    void DecrementActiveApp();

    /**
        Shutdown the current running app, then start a new app based on activeAppEnumM.
     */
    void SetCurrentApp();

    IFrameDispatcher* pFrameDispatcherM = nullptr;
    IInputPoller*     pInputPollerM = nullptr;
    ActiveAppEnum     activeAppEnumM = ACTIVE_APP_DEFAULT;
    IApp*             pActiveAppM = nullptr;

    KeyStateEnum          upKeyCurrentStateM = KEY_STATE_RELEASE;
    KeyStateEnum          downKeyCurrentStateM = KEY_STATE_RELEASE;
};

#endif /* APPMANAGER_H */