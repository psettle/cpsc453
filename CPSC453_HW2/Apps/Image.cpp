/**
file: Image.cpp
brief: Shows an openGL 2D image
notes:
    Very loosly based off of:
    https://github.com/psettle/CrappyChess/blob/master/GlObject.cpp

    (My own hobby code)
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Image.hpp"
#include "StbImage.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

Image::Image(std::string const & imagePath, IFrameDispatcher* dispatcher)
{
    GLuint vertex_buffer_object;
    GLuint uv_buffer_object;
    stbImageM = new StbImage(imagePath, STBI_rgb_alpha);

    if (stbImageM->ReadImageData() == nullptr)
    {
        std::cerr << "Invalid file: " << imagePath.c_str() << std::endl;
        return;
    }

    auto vertices = GetInitialVertices();
    auto uvs = GetInitialUVs();

    /* generate a vertex array and buffers for each array we need to pass */
    glGenVertexArrays(1, &vertexArrayHandleM);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &uv_buffer_object);
    
    /* add all the new buffers to the list of buffers to delete */
    buffersToFreeM.push_back(vertex_buffer_object);
    buffersToFreeM.push_back(uv_buffer_object);

    /* set the vertex array to bind to */
    glBindVertexArray(vertexArrayHandleM);

    /* bind an array buffer */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    /* load the points into the buffer */
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    /* tell openGL what kind of data we passed */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    /* bind the buffer to the vertex array object (at index 0)*/
    glEnableVertexAttribArray(0);

    vertexCountM = vertices.size() * 3;

    /* bind an array buffer */
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_object);
    /* load the uvs into the buffer */
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    /* tell openGL what kind of data we passed */
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    /* bind the buffer to the vertex array object (at index 1)*/
    glEnableVertexAttribArray(1);

    /* clear the vertex array object */
    glBindVertexArray(0);
    /* clear the array buffer */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Create shader for the class, if it doesn't exist */
    if (nullptr == Image::shader)
    {
        /* TODO: this is never deleted, could be deleted on system deinit, or when no polygons exist. */
        Image::shader = new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragment.glsl");
    }

    pTextureM = new Texture(stbImageM, GL_TEXTURE0, Image::shader, "image");

    /* Mark object as configured. */
    pFrameDispatcherM = dispatcher;
    pFrameDispatcherM->RegisterFrameListener(this);
}

void Image::OnFrame()
{
    Image::shader->Enable();
    pTextureM->Enable();
   
    GLuint model_matrix_uniform;

    model_matrix_uniform = glGetUniformLocation(Image::shader->GetProgramID(), "model_matrix");
    glUniformMatrix4fv(model_matrix_uniform, 1, GL_FALSE, &modelMatrixM[0][0]);

    /* set the vertex array object active */
    glBindVertexArray(vertexArrayHandleM);
    /* draw the elements */
    glDrawArrays(GL_TRIANGLES, 0, vertexCountM);
    /* clear the array object */
    glBindVertexArray(0);

    pTextureM->Disable();
    Image::shader->Disable();
}

void Image::Translate(glm::vec3 direction)
{
    RawScale(1 / currentScaleM);
    RawRotate(-currentRotationM);

    modelMatrixM *= glm::translate(direction);
    currentPos += direction;

    RawRotate(currentRotationM);
    RawScale(currentScaleM);
}

void Image::Scale(GLfloat scaleFactor)
{
    RawScale(scaleFactor);
    currentScaleM *= scaleFactor;
}

void Image::RawScale(GLfloat scaleFactor)
{
    modelMatrixM *= glm::scale(glm::vec3(scaleFactor));
}

void Image::Rotate(GLfloat rotationAngle)
{
    RawRotate(rotationAngle);
    currentRotationM += rotationAngle;
}

void Image::RawRotate(GLfloat rotationAngle)
{
    modelMatrixM *= glm::rotate(rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
}

Image::~Image()
{
    delete pTextureM;
    delete stbImageM;
    pFrameDispatcherM->UnregisterFrameListener(this);
    glDeleteBuffers(buffersToFreeM.size(), &buffersToFreeM[0]);
    glDeleteVertexArrays(1, &vertexArrayHandleM);
}

std::vector<glm::vec3> Image::GetInitialVertices() const
{
    GLfloat yPos;
    GLfloat xPos;

    if (stbImageM->ReadHeight() > stbImageM->ReadWidth())
    {
        yPos = 1.0f;
        xPos = stbImageM->ReadWidth() / (float)stbImageM->ReadHeight();
    }
    else
    {
        yPos = stbImageM->ReadHeight() / (float)stbImageM->ReadWidth();
        xPos = 1.0f;
    }

    std::vector<glm::vec3> vertices =
    {
        glm::vec3(-xPos, -yPos, 0.0f),
        glm::vec3(-xPos, yPos, 0.0f),
        glm::vec3(xPos, yPos, 0.0f),

        glm::vec3(xPos, yPos, 0.0f),
        glm::vec3(xPos, -yPos, 0.0f),
        glm::vec3(-xPos, -yPos, 0.0f)
    };

    return vertices;
}

std::vector<glm::vec2> Image::GetInitialUVs() const
{
    GLfloat yPos = 1.0f;
    GLfloat xPos = 1.0f;

    std::vector<glm::vec2> uvs =
    {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),

        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f)
    };

    return uvs;
}

Shader* Image::shader = nullptr;