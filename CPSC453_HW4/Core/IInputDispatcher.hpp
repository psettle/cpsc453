#ifndef IINPUTDISPATCHER_H
#define IINPUTDISPATCHER_H

/**
file: IInputDispatcher.hpp
brief: Interface for registering for input events.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IInputListener.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class IInputDispatcher
{
public:
    /**
        Register a listener for input events.
     */
    virtual void RegisterInputListener(IInputListener* listener) = 0;
    /**
        Unregister a listener for input events.

        return:
            true on success,
            false on failure (listener was not registered)
    */
    virtual bool UnregisterInputListener(IInputListener* listener) = 0;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* IINPUTDISPATCHER_H */