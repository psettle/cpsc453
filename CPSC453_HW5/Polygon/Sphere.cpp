/**
file: Sphere.cpp
brief: Definition of OpenGL Sphere.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Sphere.hpp"
#include "Texture.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

#define SEGMENT_COUNT           ( 300 )
#define SEGMENT_SEPERATION      ( PI / SEGMENT_COUNT )

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

Sphere::Sphere(IFrameDispatcher* dispatcher, Camera* pCamera, GLfloat radius, std::string const & textureFilename, GLfloat ambient, GLfloat diffuse)
    : pCameraM(pCamera), ambientM(ambient), diffuseM(diffuse)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;

    GLfloat theta, phi;

    theta = 0.0;

    for (uint32 i = 0; i < SEGMENT_COUNT; ++i)
    {
        phi = 0.0f;

        for (uint32 j = 0; j < SEGMENT_COUNT * 2; ++j)
        {
            glm::vec3 p0 = SphericalToCartesian(theta, phi, radius);
            glm::vec3 p1 = SphericalToCartesian(theta + SEGMENT_SEPERATION, phi, radius);
            glm::vec3 p2 = SphericalToCartesian(theta + SEGMENT_SEPERATION, phi + SEGMENT_SEPERATION, radius);
            glm::vec3 p3 = SphericalToCartesian(theta, phi + SEGMENT_SEPERATION, radius);

            glm::vec2 uv0;
            uv0.x = phi / (2 * PI);
            uv0.y = theta / PI;
            glm::vec2 uv1;
            uv1.x = phi / (2 * PI);
            uv1.y = (theta + SEGMENT_SEPERATION) / PI;
            glm::vec2 uv2;
            uv2.x = (phi + SEGMENT_SEPERATION) / (2 * PI);
            uv2.y = (theta + SEGMENT_SEPERATION) / PI;
            glm::vec2 uv3;
            uv3.x = (phi + SEGMENT_SEPERATION) / (2 * PI);
            uv3.y = theta / PI;

            if (i != SEGMENT_COUNT)
            {
                vertices.push_back(p0);
                vertices.push_back(p1);
                vertices.push_back(p2);
                uvs.push_back(uv0);
                uvs.push_back(uv1);
                uvs.push_back(uv2);
            }
           
            if (i != 0)
            {
                vertices.push_back(p2);
                vertices.push_back(p3);
                vertices.push_back(p0);
                uvs.push_back(uv2);
                uvs.push_back(uv3);
                uvs.push_back(uv0);
            }

            phi += SEGMENT_SEPERATION;
        }

        theta += SEGMENT_SEPERATION;
    }

    auto image = StbImage(textureFilename, STBI_rgb_alpha);
    Configure(dispatcher, vertices, uvs, new Texture(&image, GL_TEXTURE0));
}

void Sphere::SetUniforms()
{
    glm::mat4 model = glm::mat4(1.0f);

    for (auto mat : sceneQueueM)
    {
        model *= *mat;
    }

    glm::mat4 MVP = pCameraM->FeedMatrix(model);
    GLuint UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "MVP");
    glUniformMatrix4fv(UID, 1, GL_FALSE, &MVP[0][0]);

    UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "model");
    glUniformMatrix4fv(UID, 1, GL_FALSE, &model[0][0]);

    UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "light_pos");
    glUniform3f(UID, 0.0f, 0.0f, 0.0f);

    UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "camera_pos");
    glUniform3fv(UID, 3, &pCameraM->GetPosition()[0]);

    UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "material.ambient");
    glUniform1f(UID, ambientM);

    UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "material.diffuse");
    glUniform1f(UID, diffuseM);

    UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "material.specular");
    glUniform1f(UID, 0.0f);

    UID = glGetUniformLocation(Polygon::shader->GetProgramID(), "material.specular_exp");
    glUniform1f(UID, 1.0f);
}

glm::vec3 Sphere::SphericalToCartesian(GLfloat theta, GLfloat phi, GLfloat radius) const
{
    glm::vec3 p;

    p.x = radius * glm::sin(theta) * glm::sin(phi);
    p.y = radius * glm::cos(theta);
    p.z = radius * glm::sin(theta) * glm::cos(phi);

    return p;
}


void Sphere::AddSceneReference(glm::mat4 * reference)
{
    sceneQueueM.push_back(reference);
}