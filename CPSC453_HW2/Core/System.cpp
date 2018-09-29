/**
file: System.cpp
brief: definition of top level system driver
notes:
    Loosly based off of:
    https://github.com/psettle/CrappyChess/blob/master/System.cpp

    (My own code from a hobby project)
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "System.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/
static const std::string WINDOW_NAME = "CPSC453_HW1";

/**********************************************************
                       DECLARATIONS
**********************************************************/

static void StaticKeyCallback(GLFWwindow* pWindow, int key, int scancode, int actions, int mods);
static void StaticMouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods);
static void StaticScrollCallback(GLFWwindow* pWindow, double xoffset, double yoffset);
static void StaticMousePositionCallback(GLFWwindow* pWindow, double xpos, double ypos);

/**********************************************************
                       DEFINITIONS
**********************************************************/

static std::vector<System*> systemInstances;

System::System()
{
    /* Init glfw */
    if (!glfwInit())
    {
        return;
    }

    /* glfwWindowHint(GLFW_SAMPLES, 16); *//* 4x antialiasing */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* Using OpenGL 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* Disable deprecated features */

    /* Create a window */
    pWindowM = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.c_str(), NULL, NULL);

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

    /* enable vsync for smooth pictures */
    glfwSwapInterval(1);

    /* Register for input events */
    systemInstances.push_back(this);
    glfwSetKeyCallback(pWindowM, StaticKeyCallback);
    glfwSetMouseButtonCallback(pWindowM, StaticMouseButtonCallback);
    glfwSetScrollCallback(pWindowM, StaticScrollCallback);
    glfwSetCursorPosCallback(pWindowM, StaticMousePositionCallback);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void System::RegisterFrameListener(IFrameListener* listener, bool pushFront)
{
    if (pushFront)
    {
        frameListenersM.insert(frameListenersM.begin(), listener);
    }
    else
    {
        frameListenersM.push_back(listener);
    }
    
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

void System::RegisterInputListener(IInputListener* listener)
{
    inputListenersM.push_back(listener);
}
bool System::UnregisterInputListener(IInputListener* listener)
{
    for (uint32 i = 0; i < inputListenersM.size(); ++i)
    {
        if (inputListenersM[i] == listener)
        {
            inputListenersM.erase(inputListenersM.begin() + i);
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
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    for (uint32 i = 0; i < frameListenersM.size(); ++i)
    {
        frameListenersM[i]->OnFrame();
    }

    glfwSwapBuffers(pWindowM);
}

System::~System()
{
    glfwTerminate();

    /* Delete us from active systems. */
    for (uint32 i = 0; i < systemInstances.size(); ++i)
    {
        if (systemInstances[i] == this)
        {
            systemInstances.erase(systemInstances.begin() + i);
        }
    }

}

static void StaticKeyCallback(GLFWwindow* pWindow, int key, int scancode, int actions, int mods)
{
    for (auto system : systemInstances)
    {
        system->KeyCallback(pWindow, key, scancode, actions, mods);
    }
}

static void StaticMouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods)
{
    for (auto system : systemInstances)
    {
        system->MouseButtonCallback(pWindow, button, action, mods);
    }
}

static void StaticScrollCallback(GLFWwindow* pWindow, double xoffset, double yoffset)
{
    for (auto system : systemInstances)
    {
        system->ScrollCallback(pWindow, xoffset, yoffset);
    }
}

static void StaticMousePositionCallback(GLFWwindow* pWindow, double xpos, double ypos)
{
    for (auto system : systemInstances)
    {
        system->MousePositionCallback(pWindow, xpos, ypos);
    }
}

void System::KeyCallback(GLFWwindow* pWindow, int key, int scancode, int actions, int mods)
{
    for (auto listener : inputListenersM)
    {
        listener->OnKey(key, actions);
    }
}

void System::MouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods)
{
    for (auto listener : inputListenersM)
    {
        listener->OnMouseButton(button, action);
    }
}

void System::ScrollCallback(GLFWwindow* pWindow, double xoffset, double yoffset)
{
    for (auto listener : inputListenersM)
    {
        listener->OnScroll(yoffset);
    }
}

void System::MousePositionCallback(GLFWwindow* pWindow, double xpos, double ypos)
{
    GLint windowWidth, windowHeight;

    glfwGetWindowSize(pWindow, &windowWidth, &windowHeight);

    /* Normalize coordinates to opengl space. */
    xpos /= windowWidth;
    xpos *= 2;
    xpos -= 1;

    ypos /= windowHeight;
    ypos *= -2;
    ypos -= 1;

    for (auto listener : inputListenersM)
    {
        listener->OnMouseMove(xpos, ypos);
    }
}