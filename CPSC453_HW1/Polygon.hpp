#ifndef POLYGON_H
#define POLYGON_H

/**
file: Polygon.hpp
brief: A collection of OpenGL Triangles with a color.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "common.h"
#include "IFrameListener.hpp"
#include "IFrameDispatcher.hpp"
#include "PolygonShader.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class Polygon : public IFrameListener
{
public:
    void Configure(IFrameDispatcher* dispatcher, std::vector<glm::vec3> const & vertices, glm::vec3 const & color, glm::vec3 const & postition);

    virtual void OnFrame();

    virtual ~Polygon();
protected:

private:
    GLuint vertexArrayHandleM = 0;
    GLuint vertexCountM = 0;
    std::vector<GLuint> buffersToFreeM;

    bool isConfiguredM = false;
    IFrameDispatcher* pFrameDispatcherM = nullptr;

    static PolygonShader* shader;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* POLYGON_H */