/**
file: StarWarsApp.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "StarWarsApp.hpp"
#include "StringPolygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

#define SCROLL_PER_SECOND 0.2f
#define RESET_THRESOLD    -19.0f
#define RESET_VALUE        2.0f

/**********************************************************
                       DECLARATIONS
**********************************************************/

const std::string aNewHope =
"It is a period of civil war. Rebel spaceships, striking from a hidden base, have won their first victory against the evil Galactic Empire. \
gjquxz\
";
const std::vector<std::string> fontfiles =
{
    "fonts/AlexBrush-Regular.ttf",
    "fonts/Inconsolata.otf",
    "fonts/Lora-Italic.ttf",
};

const std::vector<GLfloat> fontscales =
{
    0.4f,
    0.4f,
    0.4f
};

const std::vector<GLfloat> resetthresh =
{
    -19.0f,
    -29.0f,
    -26.0f
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

StarWarsApp::StarWarsApp(IFrameDispatcher* dispatcher, IInputPoller* input)
    : pFrameDispatcherM(dispatcher), pInputPollerM(input), name(aNewHope), activefont(0), scrollRateM(SCROLL_PER_SECOND)
{
    if (fontscales.size() != fontfiles.size())
    {
        throw "Error fontscales size doesn't match fontfiles size!";
    }

    pFrameDispatcherM->RegisterFrameListener(this);

    CreateShapes();
}

StarWarsApp::~StarWarsApp()
{
    pFrameDispatcherM->UnregisterFrameListener(this);
    DestroyShapes();
}

void StarWarsApp::OnFrame()
{
    /* Check for arrow releases to change font. */
    ProcessFontSelectionInput();
    ProcessScrollRateInput();

    auto t = glfwGetTime();

    auto dt = t - oldTime;

    translation.x -= (float)(dt * scrollRateM);

    if (translation.x < resetthresh[activefont])
    {
        translation.x = RESET_VALUE;
    }

    for (auto& shape : activeShapesM)
    {
        shape->ApplyTranslation(translation);
    }

    oldTime = t;
}

void StarWarsApp::CreateShapes()
{
    auto offset = glm::vec3(0.0f);
    translation = glm::vec3(0.0f);
    oldTime = glfwGetTime();
    /* Offset to left side of screen, accounting for scaling that will be applied */
    offset.x = -1.0f / fontscales[activefont];

    activeShapesM.push_back(new StringPolygon(pFrameDispatcherM, name, fontfiles[activefont], fontscales[activefont], offset));
}

void StarWarsApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}

void StarWarsApp::ProcessFontSelectionInput()
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

void StarWarsApp::ProcessScrollRateInput()
{
    KeyStateEnum a_state = pInputPollerM->GetKey(GLFW_KEY_A);
    KeyStateEnum d_state = pInputPollerM->GetKey(GLFW_KEY_D);

    if (a_state != aKeyCurrentStateM)
    {
        if (a_state == KEY_STATE_RELEASE)
        {
            scrollRateM *= 0.8;
        }

        aKeyCurrentStateM = a_state;
    }

    if (d_state != dKeyCurrentStateM)
    {
        if (d_state == KEY_STATE_RELEASE)
        {
            scrollRateM *= (1.0 / 0.8);
        }

        dKeyCurrentStateM = d_state;
    }
}