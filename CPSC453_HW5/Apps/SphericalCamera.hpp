#ifndef SPHERICALCAMERA_H
#define SPHERICALCAMERA_H

/**
file: SphericalCamera.hpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Camera.hpp"
#include "IInputListener.hpp"
#include "IInputDispatcher.hpp"
#include "IFrameDispatcher.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

#define ROTATION_SPEED  ( 0.5f )
#define ZOOM_SPEED      ( 1.0f )
#define FOV             ( 90 )
#define CLOSE_LIMIT     ( 9.0f )
#define FAR_LIMIT       ( 100.0f )

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

class SphericalCamera : public Camera, public IInputListener
{
public:
    SphericalCamera(IFrameDispatcher* pFrameDispatcher, IInputDispatcher* pInputDispatcher)
        :pFrameDispatcherM(pFrameDispatcher), pInputDispatcherM(pInputDispatcher)
    {
        pInputDispatcherM->RegisterInputListener(this);
        pFrameDispatcherM->RegisterFrameListener(this);

        NewPerspective(FOV * PI / 180, WINDOW_WIDTH, WINDOW_HEIGHT, 0.1f, 1000000.0f);
        UpdateView();
    }

    void OnScroll(GLdouble scroll)
    {
        radiusM -= ZOOM_SPEED * static_cast<GLfloat>(scroll);

        if (radiusM < CLOSE_LIMIT)
        {
            radiusM = CLOSE_LIMIT;
        }

        if (radiusM > FAR_LIMIT)
        {
            radiusM = FAR_LIMIT;
        }

        UpdateView();
    }

    void OnMouseMove(GLdouble xpos, GLdouble ypos)
    {
        azimuthM -= static_cast<GLfloat>(xpos) * ROTATION_SPEED;

        if (ypos > 0.0f)
        {
            altitudeM = glm::min(altitudeM + static_cast<GLfloat>(ypos) * ROTATION_SPEED, PI - PI / 12);
        }
        else
        {
            altitudeM = glm::max(altitudeM + static_cast<GLfloat>(ypos) * ROTATION_SPEED, PI / 12);
        }

        UpdateView();
    }

    virtual ~SphericalCamera()
    {
        pFrameDispatcherM->UnregisterFrameListener(this);
        pInputDispatcherM->UnregisterInputListener(this);
    }

protected:

    void UpdateView()
    {
        glm::vec3 p;

        p.x = radiusM * glm::sin(altitudeM) * glm::sin(azimuthM);
        p.y = radiusM * glm::cos(altitudeM);
        p.z = radiusM * glm::sin(altitudeM) * glm::cos(azimuthM);

        NewView(p, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    GLfloat altitudeM = PI / 2;
    GLfloat azimuthM = 0.0f;
    GLfloat radiusM = 40.0f;

    IFrameDispatcher* pFrameDispatcherM;
    IInputDispatcher* pInputDispatcherM;
};

#endif /* SPHERICALCAMERA_H */