/**
file: SquareDiamondApp.cpp
brief: An app that shows overlayed squares and diamonds
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "ImagesApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

#define DEFAULT_IMAGE 0

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

static const std::vector<std::string> imagePaths = {
    "Images/protoss.jpg",
    "Images/CircleTest.JPG",
    "Images/f7f289d9-2a18-48d7-b3de-833bd735a605.jpg",
    "image4",
    "image5",
    "image6",
    "image7"
};

ImagesApp::ImagesApp(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher)
    : pFrameDispatcherM(frameDispatcher), pInputDispatcherM(inputDispatcher)
{
    pInputDispatcherM->RegisterInputListener(this);

    SetImage(DEFAULT_IMAGE);
}

ImagesApp::~ImagesApp()
{
    pInputDispatcherM->UnregisterInputListener(this);
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

    if (action != GLFW_RELEASE)
    {
        return;
    }

    switch (key)
    {
    case GLFW_KEY_1:
    case GLFW_KEY_2:
    case GLFW_KEY_3:
    case GLFW_KEY_4:
    case GLFW_KEY_5:
    case GLFW_KEY_6:
    case GLFW_KEY_7:
        SetImage(key - GLFW_KEY_1);
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
        image->Rotate(rotateAmount);
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
      
        image->Scale(scaleAmount);
    }   
}

void ImagesApp::OnMouseMove(GLdouble xpos, GLdouble ypos)
{
    if (isLeftMouseDownM)
    {
        glm::vec3 tranlate = glm::vec3(xpos - oldMouseXM, ypos - oldMouseYM, 0.0f);
        image->Translate(tranlate);
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
    if (image != nullptr)
    {
        delete image;
    }
    
    image = new Image(imagePaths[imageID], pFrameDispatcherM);
}