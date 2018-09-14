#ifndef BARNSLEYFERNAPP_H
#define BARNSLEYFERNAPP_H

/**
file: BarnsleyFernApp.hpp
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

class BarnsleyFernApp : public IApp
{
public:
    BarnsleyFernApp(IFrameDispatcher* dispatcher);

    ~BarnsleyFernApp();

    virtual void OnFrame();

    virtual void SetNumber(uint32 number);

    void CreateShapes();

    void DestroyShapes();

protected:

    /* Barnsley tranforms */
    glm::vec3 F1(glm::vec3 const & point);
    glm::vec3 F2(glm::vec3 const & point);
    glm::vec3 F3(glm::vec3 const & point);
    glm::vec3 F4(glm::vec3 const & point);

    uint32                  currentPointsM;
    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* BARNSLEYFERNAPP_H */