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

#include "common.h"
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
    ACTIVE_APP_NESTED_SQUARES,
    ACTIVE_APP_SPIRAL,
    ACTIVE_APP_SIERPINSKI,
    ACTIVE_APP_SIERPINSKIDOTS,
    ACTIVE_APP_BARNSLEYFERN,
    ACTIVE_APP_HILBERTSPACECURVE,

    ACTIVE_APP_COUNT,
    ACTIVE_APP_DEFAULT = ACTIVE_APP_HILBERTSPACECURVE
};

enum NumberReaderStateEnum
{
    NUMBER_READER_STATE_WAIT_FOR_KEY_PRESS,
    NUMBER_READER_STATE_WAIT_FOR_KEY_RELEASE
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
        All the parts of this assignment require an integer input
        describing the complexity of the drawing. The method runs a number
        input algorithm with the keyboard, then passes the result to the current app.
     */
    void ProcessNumberInput();

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

    NumberReaderStateEnum numberReaderStateM = NUMBER_READER_STATE_WAIT_FOR_KEY_PRESS;
    uint32                glfwPressedKeyM = GLFW_KEY_UNKNOWN;
    std::string           pressedKeyBufferM = "";

    KeyStateEnum          upKeyCurrentStateM = KEY_STATE_RELEASE;
    KeyStateEnum          downKeyCurrentStateM = KEY_STATE_RELEASE;
};

#endif /* APPMANAGER_H */