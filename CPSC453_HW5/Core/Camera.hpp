#ifndef CAMERA_H
#define CAMERA_H

/**
file: Camera.hpp
brief: Perspective Camera
notes:
    Loosly based off of:
    https://github.com/psettle/CrappyChess/blob/master/GlCamera.h

    (My own code from a hobby project)
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IFrameListener.hpp"
#include "Common.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/
class Camera : public IFrameListener {
public:

	/*
		Does required processing for a frame,
		to pass data define a function an inherited classes to pass data, and access
		data in this definintion
	*/
	virtual void OnFrame() {}

	/*
		'Looks at' a direction
	*/
	void NewView(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up);

	/*
		Creates a perspective for looking at a point
	*/
	void NewPerspective(const float& fov, const size_t width, const size_t height, const float front, const float back);

	/*
		Applies the camera effect to an input transformation, returns the resulting transform
	*/
	glm::mat4 FeedMatrix(const glm::mat4& source) const;

	/*
		Gets this cameras position in worldspace
	*/
	glm::vec3 GetPosition() const;

	/*
		Safely clears camera resources
	*/
	virtual ~Camera();
protected:
	/*
		The perspective matrix effect
	*/
	glm::mat4 ProjectionM;

	/*
		The look at matrix effect
	*/
	glm::mat4 ViewM;

	/*
		The sum camera transform, cached to increase speed
	*/
	glm::mat4 ResultCacheM;

	/*
		Window binding
	*/
	GLFWwindow* pWindowM;

	/*
		The position this camera is at
	*/
	glm::vec3 positionM;
};



#endif /* CAMERA_H */
