/**
file: NameApp.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "NameApp.hpp"
#include "StringPolygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

const std::vector<std::string> fontfiles =
{
    "fonts/AlexBrush-Regular.ttf",
    "fonts/Inconsolata.otf",
    "fonts/Lora-Italic.ttf",
    "fonts/SourceSansPro-Semibold.otf",
    "fonts/Snek-Regular 2.otf"
};

const std::vector<GLfloat> fontscales =
{
    0.6f,
    0.6f,
    0.6f,
    0.6f,
    0.39f
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

NameApp::NameApp(IFrameDispatcher* dispatcher, IInputPoller* input, const std::string& name)
    : pFrameDispatcherM(dispatcher), pInputPollerM(input), name(name), activefont(0)
{
    if (fontscales.size() != fontfiles.size())
    {
        throw "Error fontscales size doesn't match fontfiles size!";
    }

    pFrameDispatcherM->RegisterFrameListener(this);

    CreateShapes();
}

NameApp::~NameApp()
{
    pFrameDispatcherM->UnregisterFrameListener(this);
    DestroyShapes();
}

void NameApp::OnFrame()
{
    /* Check for arrow releases to change font. */
    ProcessFontSelectionInput();
}

void NameApp::CreateShapes()
{
    auto offset = glm::vec3(0.0f);

    /* Offset to left side of screen, accounting for scaling that will be applied */
    offset.x = -1.0f / fontscales[activefont];

    activeShapesM.push_back(new StringPolygon(pFrameDispatcherM, name, fontfiles[activefont], fontscales[activefont], offset));
}

void NameApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}

void NameApp::ProcessFontSelectionInput()
{
    KeyStateEnum left_state = pInputPollerM->GetKey(GLFW_KEY_LEFT);
    KeyStateEnum right_state = pInputPollerM->GetKey(GLFW_KEY_RIGHT);

    if (left_state != leftKeyCurrentStateM)
    {
        if (left_state == KEY_STATE_RELEASE)
        {
            activefont++;

            if (activefont == fontfiles.size())
            {
                activefont = 0;
            }

            DestroyShapes();
            CreateShapes();
        }

        leftKeyCurrentStateM = left_state;
    }

    if (right_state != rightKeyCurrentStateM)
    {
        if (right_state == KEY_STATE_RELEASE)
        {
            if (activefont == 0)
            {
                activefont = (uint8)fontfiles.size();
            }

            activefont--;

            DestroyShapes();
            CreateShapes();
        }

        rightKeyCurrentStateM = right_state;
    }
}