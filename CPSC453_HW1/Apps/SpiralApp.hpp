#ifndef SPIRALAPP_H
#define SPIRALAPP_H

/**
file: SpiralApp.hpp
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

class SpiralApp : public IApp
{
public:
    SpiralApp(IFrameDispatcher* dispatcher);

    ~SpiralApp();

    virtual void OnFrame();

    virtual void SetNumber(uint32 number);

    void CreateSpiral();

    void DestroySpiral();

protected:

    uint8                   currentSpiralRevolutionsM = 1;
    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SPIRALAPP_H */