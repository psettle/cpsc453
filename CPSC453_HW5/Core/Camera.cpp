/**
file: Camera.cpp
brief: definition of top level system driver
notes:
    Loosly based off of:
    https://github.com/psettle/CrappyChess/blob/master/GlCamera.cpp

    (My own code from a hobby project)
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Camera.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

glm::mat4 Camera::FeedMatrix(const glm::mat4& source) const
{
	return this->ResultCacheM * source;
}

void Camera::NewView(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up)
{
	this->ViewM = glm::lookAt(from, to, up);
	this->ResultCacheM = this->ProjectionM * this->ViewM;
	this->positionM = from;
}

void Camera::NewPerspective(const float& fov, const size_t width, const size_t height, const float front, const float back)
{
	float aspectRatio = (float)((double)width / (double)height);

	this->ProjectionM = glm::perspective(fov, aspectRatio, front, back);
	this->ResultCacheM = this->ProjectionM * this->ViewM;
}

glm::vec3 Camera::GetPosition() const
{
    return this->positionM;
}

Camera::~Camera()
{

}