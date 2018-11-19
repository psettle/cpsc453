/**
file: RayTraceApp.cpp
brief: Show Ray Traced Scenes
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "SceneParser.hpp"
#include "file_h.h"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

Scene SceneParser::ParseScene(const std::string& sceneFile)
{
    Scene scene;

    auto file = file_get_contents(sceneFile);

    auto lines = explode('\n', file);

    for (auto line : lines)
    {
        if (line.length() == 0)
        {
            continue;
        }

        if (line[0] == '#')
        {
            continue;
        }

        auto tokens = explode(' ', line);

        switch (parserState)
        {
        case PARSER_STATE_UNKNOWN:
            break;
        case PARSER_STATE_SPHERE_CENTRE:
            scene.spheres.push_back(Sphere());
            scene.spheres.back().centre = ReadVector(tokens);
            break;
        case PARSER_STATE_SPHERE_RADIUS:
            scene.spheres.back().radius = ReadFloat(tokens);
            break;
        case PARSER_STATE_SPHERE_MATERIAL:
            scene.spheres.back().material = ReadMaterial(tokens);
            break;
        case PARSER_STATE_TRIANGLE_P0:
            scene.triangles.push_back(Triangle());
            scene.triangles.back().p0 = ReadVector(tokens);
            break;
        case PARSER_STATE_TRIANGLE_P1:
            scene.triangles.back().p1 = ReadVector(tokens);
            break;
        case PARSER_STATE_TRIANGLE_P2:
            scene.triangles.back().p2 = ReadVector(tokens);
            break;
        case PARSER_STATE_TRIANGLE_MATERIAL:
            scene.triangles.back().material = ReadMaterial(tokens);
            break;
        case PARSER_STATE_PLANE_NORMAL:
            scene.planes.push_back(Plane());
            scene.planes.back().normal = ReadVector(tokens);
            break;
        case PARSER_STATE_PLANE_POINT:
            scene.planes.back().point = ReadVector(tokens);
            break;
        case PARSER_STATE_PLANE_MATERIAL:
            scene.planes.back().material = ReadMaterial(tokens);
            break;
        case PARSER_STATE_LIGHT_POINT:
            scene.lights.push_back(Light());
            scene.lights.back().position = ReadVector(tokens);
            break;
        case PARSER_STATE_LIGHT_COLOUR:
            scene.lights.back().colour = ReadVector(tokens);
            break;
        default:
            break;
        }

        NextState(tokens);
    }

    return scene;
}


glm::vec3 SceneParser::ReadVector(const std::vector<std::string>& tokens) const
{
    std::vector<std::string> floats;

    for (auto token : tokens)
    {
        if (token.length() == 0)
        {
            continue;
        }

        floats.push_back(token);
    }

    if (floats.size() < 3)
    {
        std::cerr << "Not enough tokens for ReadVector" << std::endl;
        return glm::vec3(0.0f);
    }

    glm::vec3 ret;

    ret.x = static_cast<GLfloat>(std::atof(floats[0].c_str()));
    ret.y = static_cast<GLfloat>(std::atof(floats[1].c_str()));
    ret.z = static_cast<GLfloat>(std::atof(floats[2].c_str()));

    return ret;
}

Material SceneParser::ReadMaterial(const std::vector<std::string>& tokens) const
{
    Material ret;
    std::vector<std::string> nums;

    for (auto token : tokens)
    {
        if (token.length() == 0)
        {
            continue;
        }

        nums.push_back(token);
    }

    if (nums.size() < 8)
    {
        std::cerr << "Not enough tokens for ReadMaterial" << std::endl;
        return ret;
    }

    ret.colour.r = static_cast<GLfloat>(std::atof(nums[0].c_str()));
    ret.colour.g = static_cast<GLfloat>(std::atof(nums[1].c_str()));
    ret.colour.b = static_cast<GLfloat>(std::atof(nums[2].c_str()));
    ret.ambient = static_cast<GLfloat>(std::atof(nums[3].c_str()));
    ret.diffuse = static_cast<GLfloat>(std::atof(nums[4].c_str()));
    ret.specular = static_cast<GLfloat>(std::atof(nums[5].c_str()));
    ret.specular_exp = static_cast<uint32>(std::atoi(nums[6].c_str()));
    ret.reflectivity = static_cast<GLfloat>(std::atof(nums[7].c_str()));

    return ret;
}

GLfloat SceneParser::ReadFloat(const std::vector<std::string>& tokens) const
{
    std::vector<std::string> floats;

    for (auto token : tokens)
    {
        if (token.length() == 0)
        {
            continue;
        }

        floats.push_back(token);
    }

    if (floats.size() < 1)
    {
        std::cerr << "Not enough tokens for ReadFloat" << std::endl;
        return 0.0f;
    }

    return static_cast<GLfloat>(std::atof(floats[0].c_str()));
}

void SceneParser::NextState(const std::vector<std::string>& tokens)
{
    switch (parserState)
    {
    case PARSER_STATE_UNKNOWN:
    {
        if (tokens.size() < 1)
        {
            break;
        }

        auto type = tokens[0];

        if (type == "triangle")
        {
            parserState = PARSER_STATE_TRIANGLE_P0;
        }
        else if (type == "sphere")
        {
            parserState = PARSER_STATE_SPHERE_CENTRE;
        }
        else if (type == "light")
        {
            parserState = PARSER_STATE_LIGHT_POINT;
        }
        else if (type == "plane")
        {
            parserState = PARSER_STATE_PLANE_NORMAL;
        }
    }
    break;
    case PARSER_STATE_SPHERE_CENTRE:
        parserState = PARSER_STATE_SPHERE_RADIUS;
        break;
    case PARSER_STATE_SPHERE_RADIUS:
        parserState = PARSER_STATE_SPHERE_MATERIAL;
        break;
    case PARSER_STATE_SPHERE_MATERIAL:
        parserState = PARSER_STATE_UNKNOWN;
        break;
    case PARSER_STATE_TRIANGLE_P0:
        parserState = PARSER_STATE_TRIANGLE_P1;
        break;
    case PARSER_STATE_TRIANGLE_P1:
        parserState = PARSER_STATE_TRIANGLE_P2;
        break;
    case PARSER_STATE_TRIANGLE_P2:
        parserState = PARSER_STATE_TRIANGLE_MATERIAL;
        break;
    case PARSER_STATE_TRIANGLE_MATERIAL:
        parserState = PARSER_STATE_UNKNOWN;
        break;
    case PARSER_STATE_PLANE_NORMAL:
        parserState = PARSER_STATE_PLANE_POINT;
        break;
    case PARSER_STATE_PLANE_POINT:
        parserState = PARSER_STATE_PLANE_MATERIAL;
        break;
    case PARSER_STATE_PLANE_MATERIAL:
        parserState = PARSER_STATE_UNKNOWN;
        break;
    case PARSER_STATE_LIGHT_POINT:
        parserState = PARSER_STATE_LIGHT_COLOUR;
        break;
    case PARSER_STATE_LIGHT_COLOUR:
        parserState = PARSER_STATE_UNKNOWN;
        break;
    default:
        break;
    }
}