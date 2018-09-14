#ifndef HILBERTSPACECURVEAPP_H
#define HILBERTSPACECURVEAPP_H

/**
file: HilbertSpaceCurveApp.hpp
brief: An app that makes a Barnsley Fern using iterative points.
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

class HilbertSpaceCurveApp : public IApp
{
public:
    HilbertSpaceCurveApp(IFrameDispatcher* dispatcher);

    ~HilbertSpaceCurveApp();

    virtual void OnFrame();

    virtual void SetNumber(uint32 number);

    void CreateShapes();

    void DestroyShapes();

protected:

    uint32                  currentIterationsM;
    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* HILBERTSPACECURVEAPP_H */