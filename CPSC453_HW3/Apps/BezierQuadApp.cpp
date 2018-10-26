/**
file: BezierQuadApp.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "BezierQuadApp.hpp"
#include "BezierControlLines.hpp"
#include "BezierControlPoints.hpp"
#include "Bezier.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

constexpr auto SCALE_FACTOR = 0.4f;

/**********************************************************
                       DECLARATIONS
**********************************************************/

struct BezierQuadControlPoints
{
    glm::vec3 P0;
    glm::vec3 P1;
    glm::vec3 P2;
    GLfloat scale;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

BezierQuadControlPoints curves[] =
{
    { 
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(2.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        SCALE_FACTOR
    },
    {
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(-2.0f, -1.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, 0.0f),
        SCALE_FACTOR
    },
    {
        glm::vec3(-1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        SCALE_FACTOR
    },
    {
        glm::vec3(1.2f, 0.5f, 0.0f),
        glm::vec3(2.5f, 1.0f, 0.0f),
        glm::vec3(1.3f, -0.4f, 0.0f),
        SCALE_FACTOR
    }
};

BezierQuadApp::BezierQuadApp(IFrameDispatcher* dispatcher)
    : BezierApp(dispatcher)
{
    CreateShapes();
}

void BezierQuadApp::CreateShapes()
{
    for(auto curve : curves)
    {
        activeShapesM.push_back(
            new BezierControlLines(
                pFrameDispatcherM, curve.P0, curve.P1, curve.P2, curve.scale
            )
        );

        activeShapesM.push_back(
            new Bezier(
                pFrameDispatcherM, curve.P0, curve.P1, curve.P2, curve.scale
            )
        );

        activeShapesM.push_back(
            new BezierControlPoints(
                pFrameDispatcherM, curve.P0, curve.P1, curve.P2, curve.scale
            )
        );
    }
}