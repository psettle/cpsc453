/**
file: SquareDiamondApp.cpp
brief: An app that shows overlayed squares and diamonds
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "ImagesApp.hpp"
#include "BackgroundImage.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

#define DEFAULT_BACKGROUND 0
#define DEFAULT_IMAGE 0

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

static const std::vector<std::string> backgroundPaths = {
    "Images/background1-asphalt.jpg",
    "Images/background2-marble.jpg",
    "Images/background3-wood.jpg"
};

static const std::vector<std::string> imagePaths = {
    "Images/image1-mandrill.png",
    "Images/image2-uclogo.png",
    "Images/image3-aerial.jpg",
    "Images/image4-thirsk.jpg",
    "Images/image5-pattern.png",
    "Images/image6-bubble.png",
    "Images/Codex.jpg"
};

ImagesApp::ImagesApp(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher)
    : pFrameDispatcherM(frameDispatcher), pInputDispatcherM(inputDispatcher)
{
    pInputDispatcherM->RegisterInputListener(this);

    SetBackground(DEFAULT_BACKGROUND);
    SetImage(DEFAULT_IMAGE);
}

ImagesApp::~ImagesApp()
{
    pInputDispatcherM->UnregisterInputListener(this);
    delete pImageM;
    delete pBackgroundImgM;
}

void ImagesApp::OnKey(GLint key, GLint action)
{
    if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
    {
        if (action == GLFW_RELEASE)
        {
            isShiftDownM = false;
        }
        else if (action == GLFW_PRESS)
        {
            isShiftDownM = true;
        }
    }

    if (action != GLFW_RELEASE && action != GLFW_REPEAT)
    {
        return;
    }

    switch (key)
    {
    case GLFW_KEY_1:
    case GLFW_KEY_2:
    case GLFW_KEY_3:
        if (isShiftDownM)
        {
            SetBackground(key - GLFW_KEY_1);
            break;
        }
    case GLFW_KEY_4:
    case GLFW_KEY_5:
    case GLFW_KEY_6:
    case GLFW_KEY_7:
        SetImage(key - GLFW_KEY_1);
        break;
    case GLFW_KEY_RIGHT:
        pImageM->IncrementShader();
        break;
    case GLFW_KEY_LEFT:
        pImageM->DecrementShader();
        break;
    case GLFW_KEY_UP:
        if (!pImageM->SetGaussianFilterSize(++gaussianFilterScale))
        {
            gaussianFilterScale--;
        }
        break;
    case GLFW_KEY_DOWN:
        if (!pImageM->SetGaussianFilterSize(--gaussianFilterScale))
        {
            gaussianFilterScale++;
        }
        break;
    default:
        break;
    }
}

void ImagesApp::OnScroll(GLdouble scroll)
{
    if (isShiftDownM)
    {
        GLfloat rotateAmount;
        rotateAmount = (GLfloat)(0.05f * scroll * PI_D); /* Since my mouse gives scroll in units of +/- 1, this means that 40 "clicks" is a full rotation */
        pImageM->Rotate(rotateAmount);
    }
    else
    {
        GLfloat scaleAmount;

        /* Make scaling "invertable" so that 1 tick in cancels out 1 tick out. */
        if (scroll > 0.0f)
        {
            scaleAmount = (GLfloat)(1.0f / (1.0f - 0.07f * scroll));
        }
        else
        {
            scaleAmount = (GLfloat)(1.0f + 0.07f * scroll);
        }

        pImageM->Scale(scaleAmount);
    }
}

void ImagesApp::OnMouseMove(GLdouble xpos, GLdouble ypos)
{
    if (isLeftMouseDownM)
    {
        glm::vec3 tranlate = glm::vec3(xpos - oldMouseXM, ypos - oldMouseYM, 0.0f);
        pImageM->Translate(tranlate);
    }

    oldMouseXM = xpos;
    oldMouseYM = ypos;
}

void ImagesApp::OnMouseButton(GLint button, GLint action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            isLeftMouseDownM = true;
        }
        else if(action == GLFW_RELEASE)
        {
            isLeftMouseDownM = false;
        }
    }
}

void ImagesApp::SetImage(GLuint imageID)
{
    if (pImageM != nullptr)
    {
        delete pImageM;
    }

    pImageM = new Image(imagePaths[imageID], pFrameDispatcherM);
}

void ImagesApp::SetBackground(GLuint backgroundID)
{
    if (pBackgroundImgM != nullptr)
    {
        delete pBackgroundImgM;
    }

    pBackgroundImgM = new BackgroundImage(backgroundPaths[backgroundID], pFrameDispatcherM);
}
