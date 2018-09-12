/**
file: System.cpp
brief: definition of top level system driver
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "System.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/
static const uint16 WINDOW_WIDTH = 1920;
static const uint16 WINDOW_HEIGHT = 1080;
static const std::string WINDOW_NAME = "CPSC453_HW1";
static const bool FULLSCREEN_ENABLE = false;

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

System::System()
{
    /* Init glfw */
    if (!glfwInit())
    {
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 16); /* 4x antialiasing */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* Using OpenGL 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* Disable deprecated features */

    /* Create a window */
#if FULLSCREEN_ENABLE
    pWindowM = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.c_str(), glfwGetPrimaryMonitor(), NULL);
#else
    pWindowM = glfwCreateWindow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_NAME.c_str(), NULL, NULL);
#endif

    /* if the window creation failed, return */
    if (pWindowM == NULL)
    {
        return;
    }

    /* Tell glfw about our new window. */
    glfwMakeContextCurrent(pWindowM);

    /* Initialize glew, glew makes changing platforms easy! */
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        return;
    }

    /* this keeps faces nearer to the camera on top */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    /* this tells openGL not to bother rendering faces that point away from us, it assumes
       vertexes are labeled in the correct order (so cross product gets the right direction)
       or that correct normals are provided for objects */
    glEnable(GL_CULL_FACE);

    /* enable vsync for smooth pictures */
    glfwSwapInterval(1);
}

void System::RegisterFrameListener(IFrameListener* listener)
{
    frameListenersM.push_back(listener);
}

bool System::UnregisterFrameListener(IFrameListener* listener)
{
    for (uint32 i = 0; i < frameListenersM.size(); ++i)
    {
        if (frameListenersM[i] == listener)
        {
            frameListenersM.erase(frameListenersM.begin() + i);
            return true;
        }
    }

    return false;
}

void System::RequestShutdown()
{
    shouldShutdownM = true;
}

void System::Run()
{
    while (true)
    {
        if (shouldShutdownM)
        {
            break;
        }

        if (glfwWindowShouldClose(pWindowM))
        {
            break;
        }

        Frame();
    }
}

void System::Frame()
{
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    for (auto listener : frameListenersM)
    {
        listener->OnFrame();
    }

    glfwSwapBuffers(pWindowM);
}

System::~System()
{
    glfwTerminate();
}