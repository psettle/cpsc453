#ifndef SQUAREDIAMONDAPP_H
#define SQUAREDIAMONDAPP_H

/**
file: SquareDiamondApp.hpp
brief: An app that shows overlayed squares and diamonds
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

class SquareDiamondApp : public IApp
{
public:
    SquareDiamondApp(IFrameDispatcher* dispatcher);

    ~SquareDiamondApp();

    virtual void OnFrame();

    virtual void SetNumber(uint32 number);

    void CreateShapes();

    void DestroyShapes();

protected:

    uint8                   currentShapeCountM;
    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SQUAREDIAMONDAPP_H */