#ifndef BEZIERQUADAPP_H
#define BEZIERQUADAPP_H

/**
file: BezierQuadApp.hpp
brief: Shows 4 Quadratic Bezier Curves
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

class BezierQuadApp : public BezierApp
{
public:
    BezierQuadApp(IFrameDispatcher* dispatcher);

    virtual void CreateShapes();

protected:
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* BEZIERQUADAPP_H */