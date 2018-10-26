/**
file: BezierCubeApp.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "BezierCubeApp.hpp"
#include "BezierControlLines.hpp"
#include "BezierControlPoints.hpp"
#include "Bezier.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

constexpr auto SCALE_FACTOR = 1.0f / 9.0f;

/**********************************************************
                       DECLARATIONS
**********************************************************/

struct BezierCubeControlPoints
{
    glm::vec3 P0;
    glm::vec3 P1;
    glm::vec3 P2;
    glm::vec3 P3;
    GLfloat scale;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

static BezierCubeControlPoints curves[] =
{
    {
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(4.0f, 0.0f, 0.0f),
        glm::vec3(6.0f, 2.0f, 0.0f),
        glm::vec3(9.0f, 1.0f, 0.0f),
        SCALE_FACTOR
    },
    {
        glm::vec3(8.0f, 2.0f, 0.0f),
        glm::vec3(0.0f, 8.0f, 0.0f),
        glm::vec3(0.0f, -2.0f, 0.0f),
        glm::vec3(8.0f, 4.0f, 0.0f),
        SCALE_FACTOR
    },
    {
        glm::vec3(5.0f, 3.0f, 0.0f),
        glm::vec3(3.0f, 2.0f, 0.0f),
        glm::vec3(3.0f, 3.0f, 0.0f),
        glm::vec3(5.0f, 2.0f, 0.0f),
        SCALE_FACTOR
    },
    {
        glm::vec3(3.0f, 2.2f, 0.0f),
        glm::vec3(3.5f, 2.7f, 0.0f),
        glm::vec3(3.5f, 3.3f, 0.0f),
        glm::vec3(3.0f, 3.8f, 0.0f),
        SCALE_FACTOR
    },
    {
        glm::vec3(2.8f, 3.5f, 0.0f),
        glm::vec3(2.4f, 3.8f, 0.0f),
        glm::vec3(2.4f, 3.2f, 0.0f),
        glm::vec3(2.8f, 3.5f, 0.0f),
        SCALE_FACTOR
    }
};

BezierCubeApp::BezierCubeApp(IFrameDispatcher* dispatcher)
    : BezierApp(dispatcher)
{
    CreateShapes();
}

void BezierCubeApp::CreateShapes()
{
    for (auto curve : curves)
    {
        activeShapesM.push_back(
            new Bezier(
                pFrameDispatcherM, curve.P0, curve.P1, curve.P2, curve.P3, curve.scale
            )
        );

        activeShapesM.push_back(
            new BezierControlLines(
                pFrameDispatcherM, curve.P0, curve.P1, curve.P2, curve.P3, curve.scale
            )
        );

        activeShapesM.push_back(
            new BezierControlPoints(
                pFrameDispatcherM, curve.P0, curve.P1, curve.P2, curve.P3, curve.scale
            )
        );
    }
}
