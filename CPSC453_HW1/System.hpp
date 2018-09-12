#ifndef SYSTEM_H
#define SYSTEM_H

/**
file: System.hpp
brief: declaration of top level system driver
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include <vector>

#include "IFrameListener.hpp"
#include "common.h"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/
class System
{
public:
    /**
        Initialize window and opengl.
     */
    System();

    /**
        Register a new object to receive frame events.

        This class will NOT free resources associated with listeners on removal or shutdown.
     */
    void RegisterFrameListener(IFrameListener* listener);

    /**
        Unregister an existing object that was receiving frame events.

        return:
            true on success
            false on fail (listener was not registered)
     */
    bool UnregisterFrameListener(IFrameListener* listener);

    /**
        Request that the system shutdown after freeing resources;
     */
    void RequestShutdown();

    /**
        Run the application to completion.
     */
    void Run();

    /**
        Deinit opengl, shutdown window, free resources.
     */
    ~System();

protected:

    /**
        Perform top level opengl per-frame actions,
        Dispatch frame events.
     */
    void Frame();

    /**
        Currently registered frame event listeners.
     */
    std::vector<IFrameListener*> frameListenersM;

    /**
        Has the system been initialized completely?
     */
    bool isInitializedM = false;

    /**
        Has the user flagged the system to shutdown?
     */
    bool shouldShutdownM = false;

    /**
        Pointer to the glfw window object.
     */
    GLFWwindow* pWindowM = nullptr;
};
/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SYSTEM_H */