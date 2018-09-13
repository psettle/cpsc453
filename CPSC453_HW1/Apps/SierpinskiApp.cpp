/**
file: SierpinskiApp.cpp
brief: An app that shows a partial sierpinski triangle
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "SierpinskiApp.hpp"
#include "EquilateralTriangle.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const uint8 DEFAULT_ITERATION_COUNT = 1;
static const uint8 MAX_ITERATION_COUNT = 8; /* Exponential growth, can't go very high before the program explodes. */
static const GLfloat ROOT_3 = sqrt(3.0f);

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

SierpinskiApp::SierpinskiApp(IFrameDispatcher* dispatcher)
    : currentIterationsM(DEFAULT_ITERATION_COUNT), pFrameDispatcherM(dispatcher)
{
    CreateShapes();
}

SierpinskiApp::~SierpinskiApp()
{
    DestroyShapes();
}

void SierpinskiApp::OnFrame()
{
    /* Nothing active to do, shapes are rendered individually in their own frame events. */
}

void SierpinskiApp::SetNumber(uint32 number)
{
    /* bounds check on number so we don't overflow resources. */
    if (number >= 0 && number <= MAX_ITERATION_COUNT)
    {
        currentIterationsM = number;
        /* Destroy and recreate shapes to change what is displayed,
           note:
                Could optimize by just hidding shapes that should not be displayed, that isn't done here.
                */
        DestroyShapes();
        CreateShapes();
    }
}

void SierpinskiApp::CreateShapes()
{
    GLfloat triangleLen = 1.5f;
    std::vector<glm::vec3> triangleLocations;

    /* Put the base triangle at origin */
    triangleLocations.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

    /* For each iteration, replace each triangle with 3 half sized triangles. */
    for (uint32 i = 0; i < currentIterationsM; ++i)
    {
        std::vector<glm::vec3> newTriangleLocations;
        
        triangleLen /= 2.0f;

        for (auto& location : triangleLocations)
        {
            glm::vec3 bottomLeft = glm::vec3(location.x - triangleLen / 2.0f,
                                             location.y - triangleLen / (2.0f * ROOT_3),
                                             location.z);

            glm::vec3 bottomRight = glm::vec3(location.x + triangleLen / 2.0f,
                                              location.y - triangleLen / (2.0f * ROOT_3),
                                              location.z);

            glm::vec3 top = glm::vec3(location.x,
                                      location.y + triangleLen / ROOT_3,
                                      location.z);

            newTriangleLocations.push_back(bottomLeft);
            newTriangleLocations.push_back(bottomRight);
            newTriangleLocations.push_back(top);
        }
   
        /* Replace old locations with new locations to prep for next iteration. */
        triangleLocations = newTriangleLocations;
    }

    /* Put a triangle at each final location. */
    for (auto& location : triangleLocations)
    {
        /* Color scales with screen position, but offset to allow negative locations to have color. */
        glm::vec3 color = location + glm::vec3(0.5, 0.5, 0.5);
        activeShapesM.push_back(new EquilateralTriangle(pFrameDispatcherM, triangleLen, color, location));
    }
}

void SierpinskiApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}
