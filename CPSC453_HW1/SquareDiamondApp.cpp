/**
file: SquareDiamondApp.cpp
brief: An app that shows overlayed squares and diamonds
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "SquareDiamondApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const uint8 DEFAULT_SHAPE_COUNT = 1;
static const uint8 MAX_SHAPE_COUNT = UINT8_MAX;

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
        /* Destroy and recreate shapes to change what is displayed */
        DestroyShapes();
        CreateShapes();
    }
}

void SquareDiamondApp::CreateShapes()
{
    for (uint16 i = 0; i < currentShapeCountM; ++i)
    {
        auto pSquare = new Square(pFrameDispatcherM, side_len, 0, color);

        activeShapesM.push_back(pSquare);

        auto pDiamond = new Square(pFrameDispatcherM, side_len, PI_D / 4, color);

        activeShapesM.push_back(pDiamond);
    }
}

void SquareDiamondApp::DestroyShapes()
{
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    activeShapesM.clear();
}
