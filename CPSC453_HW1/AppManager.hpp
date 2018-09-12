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

    ACTIVE_APP_COUNT,
    ACTIVE_APP_DEFAULT = ACTIVE_APP_NESTED_SQUARES
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
        All the parts of this assignment require an integer input
        describing the complexity of the drawing. The method runs a number
        input algorithm with the keyboard, and will return true when the user finishes entering
        a new number.
     */
    void ProcessNumberInput();
    void ProcessAppSelectionInput();

    void IncrementActiveApp();
    void DecrementActiveApp();

    void SetCurrentApp();

    /**
        Called on each frame if registed to a frame dispatcher
     */
    virtual void OnFrame();

    /**
        Teardown the current app.
     */
    ~AppManager();
protected:

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