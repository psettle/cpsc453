#ifndef SQUAREDIAMONDAPP_H
#define SQUAREDIAMONDAPP_H

/**
file: ImagesApp.hpp
brief: An app that shows several images
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IApp.hpp"
#include "IFrameDispatcher.hpp"
#include "IInputDispatcher.hpp"
#include "Image.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class ImagesApp : public IApp
{
public:
    ImagesApp(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher);

    ~ImagesApp();

    void OnKey(GLint key, GLint action);

    void OnScroll(GLdouble scroll);

    void OnMouseMove(GLdouble xpos, GLdouble ypos);

    void OnMouseButton(GLint button, GLint action);

protected:

    void SetImage(GLuint imageID);
    void SetBackground(GLuint backgroundID);

    Image* pImageM = nullptr;
    Image* pBackgroundImgM = nullptr;

    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    IInputDispatcher*       pInputDispatcherM = nullptr;

    bool isShiftDownM = false;
    bool isLeftMouseDownM = false;

    GLdouble oldMouseXM = 0.0f;
    GLdouble oldMouseYM = 0.0f;

    GLint gaussianFilterScale = 0;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* SQUAREDIAMONDAPP_H */