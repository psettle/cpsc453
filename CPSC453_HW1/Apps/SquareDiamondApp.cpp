/**
file: SquareDiamondApp.cpp
brief: An app that shows overlayed squares and diamonds
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "SquareDiamondApp.hpp"
#include "Square.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const uint8 DEFAULT_SHAPE_COUNT = 1;
static const uint8 MAX_SHAPE_COUNT = UINT8_MAX;
static const GLdouble SIDE_LEN_FACTOR = 1.0 / sqrt(2.0);
static const GLfloat SQUARE_DEPTH_OFFSET = -0.0001f;

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

SquareDiamondApp::SquareDiamondApp(IFrameDispatcher* dispatcher)
    : currentShapeCountM(DEFAULT_SHAPE_COUNT), pFrameDispatcherM(dispatcher)
{
    CreateShapes();
}

SquareDiamondApp::~SquareDiamondApp()
{
    DestroyShapes();
}

void SquareDiamondApp::OnFrame()
{
    /* Nothing active to do, shapes are rendered individually in their own frame events. */
}

void SquareDiamondApp::SetNumber(uint32 number)
{
    /* bounds check on number so we don't overflow resources. */
    if (number > 0 && number <= MAX_SHAPE_COUNT)
    {
        currentShapeCountM = number;
        /* Destroy and recreate shapes to change what is displayed,
           note:
                Could optimize by just hidding shapes that should not be displayed, that isn't done here.
                */
        DestroyShapes();
        CreateShapes();
    }
    else
    {
        std::cout << "Max iterations exceeded" << std::endl;
    }
}

void SquareDiamondApp::CreateShapes()
{
    GLdouble side_len = 1.9f;
    glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);

    GLfloat shade_difference = 1.0f / currentShapeCountM;

    for (uint16 i = 0; i < currentShapeCountM; ++i)
    {
        activeShapesM.push_back(new Square(pFrameDispatcherM, side_len, 0, red));
        red.x -= shade_difference;
        side_len *= SIDE_LEN_FACTOR;

        activeShapesM.push_back(new Square(pFrameDispatcherM, side_len, PI_D / 4, blue));
        blue.z -= shade_difference;
        side_len *= SIDE_LEN_FACTOR;
    }
}

void SquareDiamondApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}
