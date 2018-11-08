#ifndef IFRAMEDISPATCHER_H
#define IFRAMEDISPATCHER_H

/**
file: IFrameListener.hpp
brief: Interface for receiving frame events.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IFrameListener.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class IFrameDispatcher
{
public:
    /**
        Register a listener for frame events.
     */
    virtual void RegisterFrameListener(IFrameListener* listener, bool pushFront = false) = 0;
    /**
        Unregister a listener for frame events.

        return:
            true on success,
            false on failure (listener was not registered)
    */
    virtual bool UnregisterFrameListener(IFrameListener* listener) = 0;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* IFRAMEDISPATCHER_H */