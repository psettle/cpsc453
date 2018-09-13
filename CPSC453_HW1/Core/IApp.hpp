#ifndef IAPP_H
#define IAPP_H

/**
file: IApp.hpp
brief: Interface for "apps" (Parts of assignments)
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "common.h"
#include "IFrameListener.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class IApp : IFrameListener
{
public:
    virtual void SetNumber(uint32 number) = 0;

    virtual ~IApp() = 0;
};

inline IApp::~IApp() {}

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* IAPP_H */