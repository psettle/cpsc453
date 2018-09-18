/**
file: BarnsleyFernApp.cpp
brief: An app that shows a partial BarnsleyFern
notes:
    Transform functions modified from:
    https://en.wikipedia.org/wiki/Barnsley_fern#Computer_generation
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include <ctime>

#include "BarnsleyFernApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const uint32 DEFAULT_DOT_COUNT = 10000;
static const uint32 MAX_DOT_COUNT = UINT32_MAX;
static const GLfloat FERN_SCALE_FACTOR = 0.2f;

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

BarnsleyFernApp::BarnsleyFernApp(IFrameDispatcher* dispatcher)
    : currentPointsM(DEFAULT_DOT_COUNT), pFrameDispatcherM(dispatcher)
{
    CreateShapes();
}

BarnsleyFernApp::~BarnsleyFernApp()
{
    DestroyShapes();
}

void BarnsleyFernApp::OnFrame()
{
    /* Nothing active to do, shapes are rendered individually in their own frame events. */
}

void BarnsleyFernApp::SetNumber(uint32 number)
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
    else
    {
        std::cout << "Max dot count exceeded." << std::endl;
    }
}

void BarnsleyFernApp::CreateShapes()
{
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> colors;

    /* Make the starting point: */
    points.push_back( glm::vec3(0.0f));

    /* Seed random */
    std::srand(static_cast<uint32>(std::time(nullptr)));

    for (uint32 i = 0; i < currentPointsM - 1; ++i)
    {
        uint8 rand = std::rand() % 100;

        /* Select a transform & apply*/
        if (rand == 0)
        {
            points.push_back(F1(points[i]));
        }
        else if (rand <= 85)
        {
            points.push_back(F2(points[i]));
        }
        else if (rand <= 92)
        {
            points.push_back(F3(points[i]));
        }
        else
        {
            points.push_back(F4(points[i]));
        }
    }

    /* Apply global tranform to centre the fern */
    auto offset = glm::vec3(0.0f, -1.0f, 0.0f);
    for (auto& point : points)
    {
        point += offset;
    }

    /* Populate colors (green, it's a fern!) */
    for (uint32 i = 0; i < points.size(); ++i)
    {
        colors.push_back(glm::vec3(0.1f, 0.8f, 0.1f));
    }

    /* Create dot set. */
    auto poly = new Polygon();
    poly->Configure(pFrameDispatcherM, points, colors, glm::vec3(0.0f), GL_POINTS);
    activeShapesM.push_back(poly);
}

void BarnsleyFernApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}

glm::vec3 BarnsleyFernApp::F1(glm::vec3 const & point)
{
    return glm::vec3
            (
                0.0f,
                0.16f * point.y,
                point.z
            );
}

glm::vec3 BarnsleyFernApp::F2(glm::vec3 const & point)
{
    return glm::vec3
            (
                0.85f * point.x + 0.04 * point.y,
                -0.04f * point.x + 0.85 * point.y + 1.6f * FERN_SCALE_FACTOR,
                point.z
            );
}

glm::vec3 BarnsleyFernApp::F3(glm::vec3 const & point)
{
    return glm::vec3
            (
                0.2f * point.x - 0.26f * point.y,
                0.23f * point.x + 0.22 * point.y + 1.6f * FERN_SCALE_FACTOR,
                point.z
            );
}

glm::vec3 BarnsleyFernApp::F4(glm::vec3 const & point)
{
    return glm::vec3
            (
                -0.15f * point.x + 0.28f * point.y,
                0.26f * point.x + 0.24f * point.y + 0.44f * FERN_SCALE_FACTOR,
                point.z
            );
}
