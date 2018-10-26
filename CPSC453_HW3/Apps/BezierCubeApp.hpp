#ifndef BEZIERCUBEAPP_H
#define BEZIERCUBEAPP_H

/**
file: BezierCubeApp.hpp
brief: Shows 4 Cubic Bezier Curves
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

class BezierCubeApp : public BezierApp
{
public:
    BezierCubeApp(IFrameDispatcher* dispatcher);

    virtual void CreateShapes();

protected:
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* BEZIERCUBEAPP_H */