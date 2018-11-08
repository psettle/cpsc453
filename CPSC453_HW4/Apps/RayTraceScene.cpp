/**
file: RayTraceScene.cpp
brief: Show Ray Traced Scene
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "RayTraceScene.hpp"
#include "Polygon.hpp"
#include "SceneParser.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

constexpr auto DEFAULT_FOV_DEG = 55.0f;
constexpr auto DEFAULT_FOV = DEFAULT_FOV_DEG * PI / 180.0f;

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

RayTraceScene::RayTraceScene(IFrameDispatcher* frameDispatcher, const std::string& sceneFile)
    : pFrameDispatcherM(frameDispatcher), fovM(DEFAULT_FOV)
{
    InitializePixels();
    InitializeScene(sceneFile);
}

void RayTraceScene::InitializePixels()
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    /* Create 4 points for each pixel.
       (More points lets openGL antialias the edges) */
    for (uint32 i = 0; i < WINDOW_WIDTH; ++i)
    {
        GLfloat xm = (-WINDOW_WIDTH / 2.0f + i + 0.25f) / (WINDOW_WIDTH / 2.0f);
        GLfloat xp = (-WINDOW_WIDTH / 2.0f + i + 0.75f) / (WINDOW_WIDTH / 2.0f);
        for (uint32 j = 0; j < WINDOW_HEIGHT; ++j)
        {           
            GLfloat ym = (-WINDOW_HEIGHT / 2.0f + j + 0.25f) / (WINDOW_HEIGHT / 2.0f);
            GLfloat yp = (-WINDOW_HEIGHT / 2.0f + j + 0.75f) / (WINDOW_HEIGHT / 2.0f);

            glm::vec3 pixel;

            pixel = glm::vec3(xm, ym, 0.0f);
            vertices.push_back(pixel);
            colors.push_back(glm::vec3(0.0f));

            pixel = glm::vec3(xm, yp, 0.0f);
            vertices.push_back(pixel);
            colors.push_back(glm::vec3(0.0f));

            pixel = glm::vec3(xp, ym, 0.0f);
            vertices.push_back(pixel);
            colors.push_back(glm::vec3(0.0f));

            pixel = glm::vec3(xp, yp, 0.0f);
            vertices.push_back(pixel);
            colors.push_back(glm::vec3(0.0f));
        }
    }

    Configure(pFrameDispatcherM, vertices, colors, glm::vec3(0.0f), GL_POINTS);
}

void RayTraceScene::InitializeScene(const std::string& sceneFile)
{
    auto parser = SceneParser();

    sceneM = parser.ParseScene(sceneFile);
}

void RayTraceScene::OnFrame()
{
    /* Set uniforms to calculate rays with. */
    Polygon::shader->Enable();

    /* Distance to film. */
    GLfloat d = 1.0f / glm::tan(fovM / 2.0f);
    GLuint distance_to_film = glGetUniformLocation(Polygon::shader->GetProgramID(), "d");
    glUniform1f(distance_to_film, d);

    SphereUniforms();
    PlaneUniforms();
    TriangleUniforms();
    LightUniforms();
    CameraUniforms();

    Polygon::OnFrame();
}

void RayTraceScene::SphereUniforms()
{
    GLuint sphere_count = glGetUniformLocation(Polygon::shader->GetProgramID(), "sphere_count");
    glUniform1ui(sphere_count, sceneM.spheres.size());

    for (uint32 i = 0; i < sceneM.spheres.size(); ++i)
    {
        GLuint centre = glGetUniformLocation(Polygon::shader->GetProgramID(), ("spheres[" + std::to_string(i) + "].centre").c_str());
        glUniform3fv(centre, 1, reinterpret_cast<float*>(&(sceneM.spheres[i].centre)));

        GLuint radius = glGetUniformLocation(Polygon::shader->GetProgramID(), ("spheres[" + std::to_string(i) + "].radius").c_str());
        glUniform1f(radius, sceneM.spheres[i].radius);

        MaterialUniforms(sceneM.spheres[i].material, "spheres[" + std::to_string(i) + "]");
    }
}


void RayTraceScene::PlaneUniforms()
{
    GLuint plane_count = glGetUniformLocation(Polygon::shader->GetProgramID(), "plane_count");
    glUniform1ui(plane_count, sceneM.planes.size());

    for (uint32 i = 0; i < sceneM.planes.size(); ++i)
    {
        GLuint normal = glGetUniformLocation(Polygon::shader->GetProgramID(), ("planes[" + std::to_string(i) + "].normal").c_str());
        glUniform3fv(normal, 1, reinterpret_cast<float*>(&(sceneM.planes[i].normal)));

        GLuint point = glGetUniformLocation(Polygon::shader->GetProgramID(), ("planes[" + std::to_string(i) + "].point").c_str());
        glUniform3fv(point, 1, reinterpret_cast<float*>(&(sceneM.planes[i].point)));

        MaterialUniforms(sceneM.planes[i].material, "planes[" + std::to_string(i) + "]");
    }
}

void RayTraceScene::TriangleUniforms()
{
    GLuint triangle_count = glGetUniformLocation(Polygon::shader->GetProgramID(), "triangle_count");
    glUniform1ui(triangle_count, sceneM.triangles.size());

    for (uint32 i = 0; i < sceneM.triangles.size(); ++i)
    {
        GLuint p0 = glGetUniformLocation(Polygon::shader->GetProgramID(), ("triangles[" + std::to_string(i) + "].p0").c_str());
        glUniform3fv(p0, 1, reinterpret_cast<float*>(&(sceneM.triangles[i].p0)));

        GLuint p1 = glGetUniformLocation(Polygon::shader->GetProgramID(), ("triangles[" + std::to_string(i) + "].p1").c_str());
        glUniform3fv(p1, 1, reinterpret_cast<float*>(&(sceneM.triangles[i].p1)));

        GLuint p2 = glGetUniformLocation(Polygon::shader->GetProgramID(), ("triangles[" + std::to_string(i) + "].p2").c_str());
        glUniform3fv(p2, 1, reinterpret_cast<float*>(&(sceneM.triangles[i].p2)));

        MaterialUniforms(sceneM.triangles[i].material, "triangles[" + std::to_string(i) + "]");
    }
}

void RayTraceScene::LightUniforms()
{
    GLuint light_count = glGetUniformLocation(Polygon::shader->GetProgramID(), "light_count");
    glUniform1ui(light_count, sceneM.lights.size());

    for (uint32 i = 0; i < sceneM.lights.size(); ++i)
    {
        GLuint position = glGetUniformLocation(Polygon::shader->GetProgramID(), ("lights[" + std::to_string(i) + "].position").c_str());
        glUniform3fv(position, 1, reinterpret_cast<float*>(&(sceneM.lights[i].position)));

        GLuint colour = glGetUniformLocation(Polygon::shader->GetProgramID(), ("lights[" + std::to_string(i) + "].colour").c_str());
        glUniform3fv(colour, 1, reinterpret_cast<float*>(&(sceneM.lights[i].colour)));
    }
}

void RayTraceScene::MaterialUniforms(const Material& mat, const std::string& uniformBase)
{
    auto base = uniformBase + ".material.";

    GLuint colour = glGetUniformLocation(Polygon::shader->GetProgramID(), (base + "colour").c_str());
    glUniform3fv(colour, 1, reinterpret_cast<const float*>(&(mat.colour)));

    GLuint ambient = glGetUniformLocation(Polygon::shader->GetProgramID(), (base + "ambient").c_str());
    glUniform1f(ambient, mat.ambient);

    GLuint diffuse = glGetUniformLocation(Polygon::shader->GetProgramID(), (base + "diffuse").c_str());
    glUniform1f(diffuse, mat.diffuse);

    GLuint specular = glGetUniformLocation(Polygon::shader->GetProgramID(), (base + "specular").c_str());
    glUniform1f(specular, mat.specular);

    GLuint specular_exp = glGetUniformLocation(Polygon::shader->GetProgramID(), (base + "specular_exp").c_str());
    glUniform1ui(specular_exp, mat.specular_exp);

    GLuint reflectivity = glGetUniformLocation(Polygon::shader->GetProgramID(), (base + "reflectivity").c_str());
    glUniform1f(reflectivity, mat.reflectivity);
}

void RayTraceScene::CameraUniforms()
{
    GLuint camera_pos = glGetUniformLocation(Polygon::shader->GetProgramID(), "camera_pos");
    glUniform3fv(camera_pos, 1, reinterpret_cast<float*>(&(this->camera_pos)));

    GLuint camera_dir = glGetUniformLocation(Polygon::shader->GetProgramID(), "camera_dir");
    glUniform3fv(camera_dir, 1, reinterpret_cast<float*>(&(this->camera_dir)));

    GLuint camera_up = glGetUniformLocation(Polygon::shader->GetProgramID(), "camera_up");
    glUniform3fv(camera_up, 1, reinterpret_cast<float*>(&(this->camera_up)));
}

RayTraceScene::~RayTraceScene()
{
}



