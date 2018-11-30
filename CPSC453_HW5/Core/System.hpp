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

#include "IFrameDispatcher.hpp"
#include "IFrameListener.hpp"
#include "IInputListener.hpp"
#include "IInputDispatcher.hpp"
#include "Common.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/
class System : public IFrameDispatcher, public IInputDispatcher
{
public:
    /**
        Initialize window and opengl.
     */
    System();

    /**
        Request that the system shutdown after freeing resources;
     */
    void RequestShutdown();

    /**
        Run the application to completion.
     */
    void Run();

    /**
        Implementation of IFrameDispatcher
    */
    void RegisterFrameListener(IFrameListener* listener, bool pushFront);
    bool UnregisterFrameListener(IFrameListener* listener);

    /**
    Implementation of IInputDispatcher
*/
    void RegisterInputListener(IInputListener* listener);
    bool UnregisterInputListener(IInputListener* listener);

    /**
        Deinit opengl, shutdown window, free resources.
     */
    ~System();

    void KeyCallback(GLFWwindow* pWindow, int key, int scancode, int actions, int mods);
    void MouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods);
    void ScrollCallback(GLFWwindow* pWindow, double xoffset, double yoffset);
    void MousePositionCallback(GLFWwindow* pWindow, double xoffset, double yoffset);
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
        Currently registered input event listeners.
    */
    std::vector<IInputListener*> inputListenersM;

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