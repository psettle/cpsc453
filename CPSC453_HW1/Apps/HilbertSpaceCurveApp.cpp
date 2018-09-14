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

#include "HilbertSpaceCurveApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

static const uint32 DEAFULT_ITERATION_COUNT = 1;
static const uint32 MAX_ITERATION_COUNT = 10;

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

HilbertSpaceCurveApp::HilbertSpaceCurveApp(IFrameDispatcher* dispatcher)
    : currentIterationsM(DEAFULT_ITERATION_COUNT), pFrameDispatcherM(dispatcher)
{
    CreateShapes();
}

HilbertSpaceCurveApp::~HilbertSpaceCurveApp()
{
    DestroyShapes();
}

void HilbertSpaceCurveApp::OnFrame()
{
    /* Nothing active to do, shapes are rendered individually in their own frame events. */
}

void HilbertSpaceCurveApp::SetNumber(uint32 number)
{
    /* bounds check on number so we don't overflow resources. */
    if (number >= 1 && number <= MAX_ITERATION_COUNT)
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

void HilbertSpaceCurveApp::CreateShapes()
{  
    std::vector<glm::vec3> lines;
    std::vector<glm::vec3> colors;

    GLfloat maxLen = 1.8f;

    /* Create the 1st iteration: */
    lines.push_back(glm::vec3(-maxLen / 2.0f, maxLen / 2.0f, 0.0f));
    lines.push_back(glm::vec3(-maxLen / 2.0f, -maxLen / 2.0f, 0.0f));

    lines.push_back(glm::vec3(-maxLen / 2.0f, -maxLen / 2.0f, 0.0f));
    lines.push_back(glm::vec3(maxLen / 2.0f, -maxLen / 2.0f, 0.0f));

    lines.push_back(glm::vec3(maxLen / 2.0f, -maxLen / 2.0f, 0.0f));
    lines.push_back(glm::vec3(maxLen / 2.0f, maxLen / 2.0f, 0.0f));

    for (uint32 i = 1; i < currentIterationsM; ++i)
    {
        /* For each iteration, copy the current set of lines 4 times, transform them to correct positons,
           then combine the arrays by linking at the corners with new lines. */

        /* The amount each copy must be scaled and translated depends on how many iterations are done,
           because the length of the connecting lines gets smaller each iteration. 
           
           when going from iteration i - 1, to i:

           scale existing lines by: (2^i-1)/(2^(i+1)-1)
           translate by:            (2^(i-1))/(2^(i+1)-1) * sideLen     <- where sideLen is the length of a line in the first iteration.       
           */

        GLfloat scaleFactor = (GLfloat)(glm::pow(2, i) - 1)/(GLfloat)(glm::pow(2, i + 1) - 1);
        GLfloat offsetFactor = (GLfloat)(glm::pow(2, i - 1))/(GLfloat)(glm::pow(2, i + 1) - 1);

        /* Scalethe existing set */
        for (auto& point : lines)
        {
            point *= scaleFactor;
        }

        /* Create 4 copies */
        std::vector<glm::vec3> topLeft = lines;
        std::vector<glm::vec3> topRight = lines;
        std::vector<glm::vec3> bottomLeft = lines;
        std::vector<glm::vec3> bottomRight = lines;

        /* Rotate top sections: */
        glm::mat4 topLeftRotationMatrix = glm::rotate(PI / 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        for (auto& point : topLeft)
        {
            point = glm::vec3(glm::vec4( point, 0.0f ) * topLeftRotationMatrix);

            /* Reflect to keep visual line order consistent with array. */
            point *= glm::vec3(-1.0f, 1.0f, 1.0f);
        }

        glm::mat4 topRightRotationMatrix = glm::rotate(-PI / 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        for (auto& point : topRight)
        {
            point = glm::vec3(glm::vec4(point, 0.0f) * topRightRotationMatrix);

            /* Reflect to keep visual line order consistent with array. */
            point *= glm::vec3(-1.0f, 1.0f, 1.0f);
        }

        /* Translate sections to correct quadrant: */
        glm::vec3 topLeftOffset = glm::vec3(-maxLen * offsetFactor, maxLen * offsetFactor, 0.0f);
        for (auto& point : topLeft)
        {
            point += topLeftOffset;
        }

        glm::vec3 topRightOffset = glm::vec3(maxLen * offsetFactor, maxLen * offsetFactor, 0.0f);
        for (auto& point : topRight)
        {
            point += topRightOffset;
        }

        glm::vec3 bottomLeftOffset = glm::vec3(-maxLen * offsetFactor, -maxLen * offsetFactor, 0.0f);
        for (auto& point : bottomLeft)
        {
            point += bottomLeftOffset;
        }

        glm::vec3 bottomRightOffset = glm::vec3(maxLen * offsetFactor, -maxLen * offsetFactor, 0.0f);
        for (auto& point : bottomRight)
        {
            point += bottomRightOffset;
        }

        /* Combine new segments */
        lines.clear();

        lines.insert(lines.end(), topLeft.begin(), topLeft.end());

        /* Insert a fill line: */
        lines.push_back(topLeft.back());
        lines.push_back(bottomLeft.front());

        lines.insert(lines.end(), bottomLeft.begin(), bottomLeft.end());

        /* Insert a fill line: */
        lines.push_back(bottomLeft.back());
        lines.push_back(bottomRight.front());

        lines.insert(lines.end(), bottomRight.begin(), bottomRight.end());

        /* Insert a fill line: */  
        lines.push_back(bottomRight.back());
        lines.push_back(topRight.front());

        lines.insert(lines.end(), topRight.begin(), topRight.end());
    }

    /* time to color the lines, luckily then are in the same order in the array as they appear graphically! */
    glm::vec3 initialColor = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 endColor = glm::vec3(0.0f, 0.0f, 1.0f);

    glm::vec3 colorDiff = endColor - initialColor;

    /* Change color along the continous line to see how space it filled */
    for (uint32 i = 0; i < lines.size(); ++i)
    {
        /* Round up to an even i, so that the end of 1 line and the start of the next are the same color */
        uint32 even_i = i + (i & 0x01);

        glm::vec3 color = initialColor + colorDiff * (GLfloat)even_i / (GLfloat)lines.size();

        colors.push_back(color);
    }

    /* Create line set. */
    auto poly = new Polygon();
    poly->Configure(pFrameDispatcherM, lines, colors, glm::vec3(0.0f), GL_LINES);
    activeShapesM.push_back(poly);
}

void HilbertSpaceCurveApp::DestroyShapes()
{
    /* Delete all the polygons */
    for (auto shape : activeShapesM)
    {
        delete shape;
    }

    /* Empty the array now that that's done. */
    activeShapesM.clear();
}