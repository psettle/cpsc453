#ifndef IINPUTPOLLER_H
#define IINPUTPOLLER_H

/**
file: IFrameListener.hpp
brief: Interface for receiving frame events.
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

enum KeyStateEnum
{
    KEY_STATE_RELEASE = GLFW_RELEASE,
    KEY_STATE_PRESS = GLFW_PRESS,
    KEY_STATE_REPEAT = GLFW_REPEAT,

    KEY_STATE_COUNT
};

class IInputPoller
{
public:
    /**
        Get the current state of a key:
            glfw_key_enum, the glfw key enums, ex: GLFW_KEY_ESCAPE

        return:
            the state the key is in
     */
    virtual KeyStateEnum GetKey(uint16 glfw_key_enum) = 0;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* IINPUTPOLLER_H */