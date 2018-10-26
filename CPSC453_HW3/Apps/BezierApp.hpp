#ifndef BEZIERAPP_H
#define BEZIERAPP_H

/**
file: BeizerApp.hpp
brief: Abstract App for rendering bezier curves
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IApp.hpp"
#include "IFrameDispatcher.hpp"
#include "Polygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class BezierApp : public IApp
{
public:
    BezierApp(IFrameDispatcher* dispatcher);

    virtual ~BezierApp();

    virtual void OnFrame();

    virtual void CreateShapes() = 0;

    void DestroyShapes();

protected:

    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* BEZIERAPP_H */