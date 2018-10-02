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

#define SIGMA 200.0f /* This is quite extreme, and it makes the filter stangley chuncky, but it allows you to still see changes up to several hundred pixels. */
#define E     2.718281828459045235360287471352662497757247093699959574966967627724076630353f
#define MAX_FILTER_SIZE 401 /* Max kernal size is 401x401, which covers essentially the whole image. */

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

enum ActiveShaderEnum
{
    ACTIVE_SHADER_PLAIN,
    ACTIVE_SHADER_GREY_1,
    ACTIVE_SHADER_GREY_2,
    ACTIVE_SHADER_GREY_3,
    ACTIVE_SHADER_SEPIA,
    ACTIVE_SHADER_HALLOWEEN, /* Switched the R & G values, makes things look orange & green kinda. */
    ACTIVE_SHADER_VERTICAL_SOBEL,
    ACTIVE_SHADER_HORIZONTAL_SOBEL,
    ACTIVE_SHADER_UNSHARP_MASK,
    ACTIVE_SHADER_GAUSSIAN_3x3,
    ACTIVE_SHADER_GAUSSIAN_5x5,
    ACTIVE_SHADER_GAUSSIAN_7x7,
    ACTIVE_SHADER_GAUSSIAN_NxN,

    ACTIVE_SHADER_COUNT,
    ACTIVE_SHADER_DEFAULT = ACTIVE_SHADER_PLAIN,
    ACTIVE_SHADER_COUNT_RESOLUTION_REQUIRED_LINE = ACTIVE_SHADER_VERTICAL_SOBEL
};

Image::Image(std::string const & imagePath, IFrameDispatcher* dispatcher)
    : activeShaderM(ACTIVE_SHADER_DEFAULT)
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

    SetShader();
    pTextureM = new Texture(stbImageM, GL_TEXTURE0);

    SetGaussianFilterSize(0);
  
    /* Mark object as configured. */
    pFrameDispatcherM = dispatcher;
    pFrameDispatcherM->RegisterFrameListener(this);
}

void Image::OnFrame()
{
    Shader* s;
    Texture* t = pTextureM;

    renderPipelineM.ClearPipe();

    for (uint32 i = 0; i < shaderQueueM.size(); ++i)
    {
        s = shaderQueueM[i];

        renderPipelineM.StartRender(t, s);

        /* Not all of these apply to every shader, it fails silently if it does not apply. */
        GLuint model_matrix_uniform = glGetUniformLocation(s->GetProgramID(), "model_matrix");
        glUniformMatrix4fv(model_matrix_uniform, 1, GL_FALSE, &modelMatrixM[0][0]);

        GLuint filter_size_uniform = glGetUniformLocation(s->GetProgramID(), "filter_size");
        glUniform1i(filter_size_uniform, gaussianFilter.size());

        GLuint filter_uniform = glGetUniformLocation(s->GetProgramID(), "filter_1d");
        glUniform1fv(filter_uniform, gaussianFilter.size(), gaussianFilter.data());

        GLuint res_uniform = glGetUniformLocation(s->GetProgramID(), "resolution");
        glUniform2i(res_uniform, stbImageM->ReadWidth(), stbImageM->ReadHeight());
        

        if (i == shaderQueueM.size() - 1)
        {
            renderPipelineM.EndRender(true, vertexArrayHandleM, vertexCountM);
        }
        else
        {
            t = renderPipelineM.EndRender(false, 0, vertexCountM);
        }
    }

    return; 
}

void Image::Translate(glm::vec3 direction)
{
    RawScale(1 / currentScaleM);
    RawRotate(-currentRotationM);

    modelMatrixM *= glm::translate(direction);
    currentPosM += direction;

    RawRotate(currentRotationM);
    RawScale(currentScaleM);
}

void Image::Scale(GLfloat scaleFactor)
{
    RawScale(scaleFactor);
    currentScaleM *= scaleFactor;

    /* Also scale the position and translate to zoom on centre */
    auto newPos = currentPosM * scaleFactor;
    auto translate = newPos - currentPosM;
    Translate(translate);
}

void Image::RawScale(GLfloat scaleFactor)
{
    modelMatrixM *= glm::scale(glm::vec3(scaleFactor));
}

void Image::Rotate(GLfloat rotationAngle)
{
    RawRotate(rotationAngle);
    currentRotationM += rotationAngle;

    /* Apply polar rotation on position so it appears to rotate on centre of screen */
    auto newPos = glm::rotate(rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(currentPosM, 0.0f);
    Translate((glm::vec3)newPos - currentPosM);
}

void Image::RawRotate(GLfloat rotationAngle)
{
    modelMatrixM *= glm::rotate(rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Image::IncrementShader()
{
    switch (activeShaderM)
    {
    case ACTIVE_SHADER_PLAIN:
        activeShaderM = ACTIVE_SHADER_GREY_1;
        break;
    case ACTIVE_SHADER_GREY_1:
        activeShaderM = ACTIVE_SHADER_GREY_2;
        break;
    case ACTIVE_SHADER_GREY_2:
        activeShaderM = ACTIVE_SHADER_GREY_3;
        break;
    case ACTIVE_SHADER_GREY_3:
        activeShaderM = ACTIVE_SHADER_SEPIA;
        break;
    case ACTIVE_SHADER_SEPIA:
        activeShaderM = ACTIVE_SHADER_HALLOWEEN;
        break;
    case ACTIVE_SHADER_HALLOWEEN:
        activeShaderM = ACTIVE_SHADER_VERTICAL_SOBEL;
        break;
    case ACTIVE_SHADER_VERTICAL_SOBEL:
        activeShaderM = ACTIVE_SHADER_HORIZONTAL_SOBEL;
        break;
    case ACTIVE_SHADER_HORIZONTAL_SOBEL:
        activeShaderM = ACTIVE_SHADER_UNSHARP_MASK;
        break;
    case ACTIVE_SHADER_UNSHARP_MASK:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_3x3;
        break;
    case ACTIVE_SHADER_GAUSSIAN_3x3:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_5x5;
        break;
    case ACTIVE_SHADER_GAUSSIAN_5x5:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_7x7;
        break;
    case ACTIVE_SHADER_GAUSSIAN_7x7:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_NxN;
        break;
    case ACTIVE_SHADER_GAUSSIAN_NxN:
        activeShaderM = ACTIVE_SHADER_PLAIN;
        break;
    default:
        std::cerr << "Unknown shader" << std::endl;
        break;
    }

    SetShader();
}

void Image::DecrementShader()
{
    switch (activeShaderM)
    {
    case ACTIVE_SHADER_PLAIN:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_NxN;
        break;
    case ACTIVE_SHADER_GREY_1:
        activeShaderM = ACTIVE_SHADER_PLAIN;
        break;
    case ACTIVE_SHADER_GREY_2:
        activeShaderM = ACTIVE_SHADER_GREY_1;
        break;
    case ACTIVE_SHADER_GREY_3:
        activeShaderM = ACTIVE_SHADER_GREY_2;
        break;
    case ACTIVE_SHADER_SEPIA:
        activeShaderM = ACTIVE_SHADER_GREY_3;
        break;
    case ACTIVE_SHADER_HALLOWEEN:
        activeShaderM = ACTIVE_SHADER_SEPIA;
        break;
    case ACTIVE_SHADER_VERTICAL_SOBEL:
        activeShaderM = ACTIVE_SHADER_HALLOWEEN;
        break;
    case ACTIVE_SHADER_HORIZONTAL_SOBEL:
        activeShaderM = ACTIVE_SHADER_VERTICAL_SOBEL;
        break;
    case ACTIVE_SHADER_UNSHARP_MASK:
        activeShaderM = ACTIVE_SHADER_HORIZONTAL_SOBEL;
        break;
    case ACTIVE_SHADER_GAUSSIAN_3x3:
        activeShaderM = ACTIVE_SHADER_UNSHARP_MASK;
        break;
    case ACTIVE_SHADER_GAUSSIAN_5x5:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_3x3;
        break;
    case ACTIVE_SHADER_GAUSSIAN_7x7:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_5x5;
        break;
    case ACTIVE_SHADER_GAUSSIAN_NxN:
        activeShaderM = ACTIVE_SHADER_GAUSSIAN_7x7;
        break;
    default:
        std::cerr << "Unknown shader" << std::endl;
        break;
    }

    SetShader();
}

void Image::SetShader()
{
    for (auto s : shaderQueueM)
    {
        delete s;
    }

    shaderQueueM.clear();

    /* Effect can be made by an arbitrary number of shaders, the first n-1 shaders
       are rendered on alternating frame buffers, before the n'th shader is rendered to screen */

    switch (activeShaderM)
    {
    case ACTIVE_SHADER_PLAIN:
        std::cout << "ACTIVE_SHADER_PLAIN" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragment.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_GREY_1:
        std::cout << "ACTIVE_SHADER_GREY_1" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentGrey1.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_GREY_2:
        std::cout << "ACTIVE_SHADER_GREY_2" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentGrey2.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_GREY_3:
        std::cout << "ACTIVE_SHADER_GREY_3" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentGrey3.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_SEPIA:
        std::cout << "ACTIVE_SHADER_SEPIA" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentSepia.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_HALLOWEEN:
        std::cout << "ACTIVE_SHADER_HALLOWEEN" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentHalloween.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_VERTICAL_SOBEL:
        std::cout << "ACTIVE_SHADER_VERTICAL_SOBEL" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentVerticalSobel.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_HORIZONTAL_SOBEL:
        std::cout << "ACTIVE_SHADER_HORIZONTAL_SOBEL" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentHorizontalSobel.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_UNSHARP_MASK:
        std::cout << "ACTIVE_SHADER_UNSHARP_MASK" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentUnsharpMask.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_GAUSSIAN_3x3:
        std::cout << "ACTIVE_SHADER_GAUSSIAN_3x3" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragment2DGaussian3x3.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_GAUSSIAN_5x5:
        std::cout << "ACTIVE_SHADER_GAUSSIAN_5x5" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragment2DGaussian5x5.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_GAUSSIAN_7x7:
        std::cout << "ACTIVE_SHADER_GAUSSIAN_7x7" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragment2DGaussian7x7.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    case ACTIVE_SHADER_GAUSSIAN_NxN:
        std::cout << "ACTIVE_SHADER_GAUSSIAN_NxN" << std::endl;
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentGaussianNHorizontal.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertexPassthrough.glsl", "shaders/ImageFragmentGaussianNVertical.glsl"));
        shaderQueueM.push_back(new Shader("shaders/ImageVertex.glsl", "shaders/ImageFragmentPassthrough.glsl"));
        break;
    default:
        std::cerr << "Unknown shader" << std::endl;
        break;
    }
}

bool Image::SetGaussianFilterSize(GLint size)
{
    size = size * 2 + 1;

    if (size < 0 || size > MAX_FILTER_SIZE)
    {
        std::cout << "Gaussian filter too small or too large: " << size << std::endl;
        return false;
    }
    else
    {
        std::cout << "Gaussian filter set to: " << size << std::endl;
    }

    gaussianFilter = GetGaussianFilter(size);

    return true;
}

Image::~Image()
{
    delete pTextureM;
    for (auto s : shaderQueueM)
    {
        delete s;
    }
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

std::vector<GLfloat> Image::GetGaussianFilter(GLint width) const
{
    std::vector<GLfloat> filter;

    GLfloat sum = 0.0f;

    for (int i = -width / 2; i <= width / 2; ++i)
    {
        GLfloat exponent = -1.0f * (i * i) / (2 * SIGMA * SIGMA);
        GLfloat factor = 1.0f / glm::sqrt(2 * PI * SIGMA * SIGMA);

        GLfloat gauss = factor * glm::pow(E, exponent);

        filter.push_back(gauss);

        sum += filter.back();
    }

    /* Normalize */
    for (uint32 i = 0; i < filter.size(); ++i)
    {
        filter[i] /= sum;
    }
    
    return filter;
}