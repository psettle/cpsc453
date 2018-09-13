#ifndef SIERPINSKIDOTSAPP_H
#define SIERPINSKIDOTSAPP_H

/**
file: SierpinskiDotsApp.hpp
brief: An app that makes a Sierpinski Triangle using iterative points.
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

class SierpinskiDotsApp : public IApp
{
public:
    SierpinskiDotsApp(IFrameDispatcher* dispatcher);

    ~SierpinskiDotsApp();

    virtual void OnFrame();

    virtual void SetNumber(uint32 number);

    void CreateShapes();

    void DestroyShapes();

protected:

    uint32                  currentPointsM = 1000;
    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SIERPINSKIDOTSAPP_H */