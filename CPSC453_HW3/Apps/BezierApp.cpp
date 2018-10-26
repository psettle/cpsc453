/**
file: BezierApp.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "BezierApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

BezierApp::BezierApp(IFrameDispatcher* dispatcher)
    : pFrameDispatcherM(dispatcher)
{
}

BezierApp::~BezierApp()
{
    DestroyShapes();
}

void BezierApp::OnFrame()
{
    /* Nothing active to do, shapes are rendered individually in their own frame events. */
}

void BezierApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}
