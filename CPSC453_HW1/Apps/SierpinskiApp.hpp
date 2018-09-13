#ifndef SIERPINSKIAPP_H
#define SIERPINSKIAPP_H

/**
file: SierpinskiApp.hpp
brief: An app that shows a Sierpinski triangle at various iterations.
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

class SierpinskiApp : public IApp
{
public:
    SierpinskiApp(IFrameDispatcher* dispatcher);

    ~SierpinskiApp();

    virtual void OnFrame();

    virtual void SetNumber(uint32 number);

    void CreateShapes();

    void DestroyShapes();

protected:

    uint8                   currentIterationsM = 1;
    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SIERPINSKIAPP_H */