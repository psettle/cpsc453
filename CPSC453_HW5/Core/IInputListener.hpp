#ifndef IINPUTLISTENER_H
#define IINPUTLISTENER_H

/**
file: IInputListener.hpp
brief: Interface for receiving input events.
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

class IInputListener
{
public:
    virtual void OnKey(GLint key, GLint action) {};
    virtual void OnMouseButton(GLint button, GLint action) {};
    virtual void OnScroll(GLdouble scroll) {};
    virtual void OnMouseMove(GLdouble xpos, GLdouble ypos) {};
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* IINPUTLISTENER_H */