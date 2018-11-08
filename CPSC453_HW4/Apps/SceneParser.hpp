#ifndef SCENEPARSER_H
#define SCENEPARSER_H

/**
file: SceneParser.hpp
brief: Parse Scene Files
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

enum ParserStateEnum
{
PARSER_STATE_UNKNOWN,
PARSER_STATE_SPHERE_CENTRE,
PARSER_STATE_SPHERE_RADIUS,
PARSER_STATE_SPHERE_MATERIAL,
PARSER_STATE_TRIANGLE_P0,
PARSER_STATE_TRIANGLE_P1,
PARSER_STATE_TRIANGLE_P2,
PARSER_STATE_TRIANGLE_MATERIAL,
PARSER_STATE_PLANE_NORMAL,
PARSER_STATE_PLANE_POINT,
PARSER_STATE_PLANE_MATERIAL,
PARSER_STATE_LIGHT_POINT,

PARSER_STATE_COUNT,
PARSER_STATE_DEFAULT = PARSER_STATE_UNKNOWN
};

struct Material
{
    glm::vec3 colour;  
    GLfloat   ambient = 0.0f;
    GLfloat   diffuse = 1.0f;
    GLfloat   specular = 0.0f;
    uint32    specular_exp = 8;
    GLfloat   reflectivity = 0.0f;
};

struct Light
{
    glm::vec3 position;
    glm::vec3 colour;
};

struct Plane
{
    Material  material;
    glm::vec3 normal;
    glm::vec3 point;
};

struct Sphere
{
    Material  material;
    glm::vec3 centre;
    GLfloat   radius;
};

struct Triangle
{
    Material  material;
    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;
};

struct Scene
{
    std::vector<Light> lights;
    std::vector<Plane> planes;
    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
};

class SceneParser
{
public:
    Scene ParseScene(const std::string& sceneFile);

private:

    glm::vec3 ReadVector(const std::vector<std::string>& tokens) const;

    Material ReadMaterial(const std::vector<std::string>& tokens) const;

    GLfloat ReadFloat(const std::vector<std::string>& tokens) const;

    void NextState(const std::vector<std::string>& tokens);

    ParserStateEnum parserState = PARSER_STATE_DEFAULT;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SCENEPARSER_H */


