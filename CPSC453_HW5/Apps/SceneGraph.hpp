#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

/**
file: SceneGraph.hpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Common.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

struct SceneGraph
{
public:
    glm::mat4               sunToWorld = glm::mat4(1.0f);       /* Sun reference frame to world reference frame */
    glm::mat4               sunRotation = glm::mat4(1.0f);      /* A reference frame in which the sun is rotated about it's origin */
    glm::mat4               sunSpin = glm::mat4(1.0f);          /* Orbital spin */
    glm::mat4               earthToSun = glm::mat4(1.0f);       /* Earth reference frame to sun reference frame */
    glm::mat4               earthRotation = glm::mat4(1.0f);    /* A reference frame in which the earth is rotated about it's origin */
    glm::mat4               earthSpin = glm::mat4(1.0f);        /* Orbital spin */
    glm::mat4               moonToEarth = glm::mat4(1.0f);      /* Moon reference frame to earth reference frame */
    glm::mat4               moonRotation = glm::mat4(1.0f);
    glm::mat4               moonSpin = glm::mat4(1.0f);        /* Orbital spin */
    glm::mat4               marsToSun = glm::mat4(1.0f);       /* Mars reference frame to sun reference frame */
    glm::mat4               marsRotation = glm::mat4(1.0f);    /* A reference frame in which mars is rotated about it's origin */
    glm::mat4               marsSpin = glm::mat4(1.0f);        /* Orbital spin */
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SCENEGRAPH_H */