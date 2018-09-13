/**
file: SierpinskiDotsApp.cpp
brief: An app that shows a partial sierpinski triangle
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include <ctime>

#include "SierpinskiDotsApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const uint32 DEFAULT_DOT_COUNT = 10000;
static const uint32 MAX_DOT_COUNT = UINT32_MAX;
static const GLfloat ROOT_3 = sqrt(3.0f);

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

SierpinskiDotsApp::SierpinskiDotsApp(IFrameDispatcher* dispatcher)
    : currentPointsM(DEFAULT_DOT_COUNT), pFrameDispatcherM(dispatcher)
{
    CreateShapes();
}

SierpinskiDotsApp::~SierpinskiDotsApp()
{
    DestroyShapes();
}

void SierpinskiDotsApp::OnFrame()
{
    /* Nothing active to do, shapes are rendered individually in their own frame events. */
}

void SierpinskiDotsApp::SetNumber(uint32 number)
{
    /* bounds check on number so we don't overflow resources. */
    if (number >= 0 && number <= MAX_DOT_COUNT)
    {
        currentPointsM = number;
        /* Destroy and recreate shapes to change what is displayed,
           note:
                Could optimize by just hidding shapes that should not be displayed, that isn't done here.
                */
        DestroyShapes();
        CreateShapes();
    }
}

void SierpinskiDotsApp::CreateShapes()
{
    GLfloat sideLen = 1.5f;
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> colors;

    /* Make the 3 starting points: */
    glm::vec3 top = glm::vec3(0.0f, sideLen / ROOT_3, 0.0f);
    glm::vec3 left = glm::vec3(-sideLen / 2.0f, -sideLen / (ROOT_3 * 2.0f), 0.0f);
    glm::vec3 right = glm::vec3(sideLen / 2.0f, -sideLen / (ROOT_3 * 2.0f), 0.0f);

    /* Add to points array */
    points.push_back(top);
    points.push_back(left);
    points.push_back(right);

    glm::vec3 activePoint;

    /* Randomly assign initial point: */
    std::srand(static_cast<uint32>(std::time(nullptr)));
    activePoint = points[std::rand() % 3];

    for (uint32 i = 3; i < currentPointsM; ++i)
    {
        /* Pick a random initial point */
        glm::vec3 randPoint = points[std::rand() % 3];

        /* Calculate halfway point to active point */
        glm::vec3 halfway = (randPoint + activePoint) / 2.0f;
        points.push_back(halfway);

        /* Update active point */
        activePoint = halfway;
    }

    /* Populate colors */
    for (auto point : points)
    {
        colors.push_back(point + glm::vec3(0.5f));
    }

    /* Create dot set. */
    auto poly = new Polygon();
    poly->Configure(pFrameDispatcherM, points, colors, glm::vec3(0.0f), GL_POINTS);
    activeShapesM.push_back(poly);
}

void SierpinskiDotsApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}
