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
#include "IInputListener.hpp"
#include "IInputDispatcher.hpp"
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
    ACTIVE_APP_RAY_TRACE,

    ACTIVE_APP_COUNT,
    ACTIVE_APP_DEFAULT = ACTIVE_APP_RAY_TRACE
};

class AppManager: public IFrameListener, public IInputListener
{
public:
    /**
        Initialize the appmanager and boot the default app
     */
    AppManager(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher);

    /**
        Called on each frame if registed to a frame dispatcher
     */
    virtual void OnFrame();

    virtual void OnKey(GLint key, GLint action);

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
    IInputDispatcher* pInputDispatcherM = nullptr;
    ActiveAppEnum     activeAppEnumM;
    IApp*             pActiveAppM = nullptr;
};

#endif /* APPMANAGER_H */
