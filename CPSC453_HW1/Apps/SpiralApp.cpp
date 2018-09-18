/**
file: SpiralApp.cpp
brief: An app that shows overlayed squares and diamonds
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "SpiralApp.hpp"
#include "Spiral.hpp"
#include "Circle.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const uint8 DEFAULT_SPIRAL_TWISTS = 1;
static const uint8 MAX_SPIRAL_TWISTS = UINT8_MAX;
static const uint32 LINES_PER_TWIST = 1000;

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

SpiralApp::SpiralApp(IFrameDispatcher* dispatcher)
    : currentSpiralRevolutionsM(DEFAULT_SPIRAL_TWISTS), pFrameDispatcherM(dispatcher)
{
    CreateSpiral();
}

SpiralApp::~SpiralApp()
{
    DestroySpiral();
}

void SpiralApp::OnFrame()
{
    /* Nothing active to do, shapes are rendered individually in their own frame events. */
}

void SpiralApp::SetNumber(uint32 number)
{
    /* bounds check on number so we don't overflow resources. */
    if (number > 0 && number <= MAX_SPIRAL_TWISTS)
    {
        currentSpiralRevolutionsM = number;
        /* Destroy and recreate shapes to change what is displayed,
           note:
                Could optimize by just hidding shapes that should not be displayed, that isn't done here.
                */
        DestroySpiral();
        CreateSpiral();
    }
    else
    {
        std::cout << "Max twists exceeded" << std::endl;
    }
}

void SpiralApp::CreateSpiral()
{
    glm::vec3 origin_color = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 tip_color = glm::vec3(0.0f, 1.0f, 0.0f);

    GLfloat maxRadius = 1.0f;

    activeShapesM.push_back(new Spiral(pFrameDispatcherM, currentSpiralRevolutionsM, maxRadius, LINES_PER_TWIST, origin_color, tip_color));
}

void SpiralApp::DestroySpiral()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}
