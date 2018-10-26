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

#include "Common.hpp"
#include "IFrameListener.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class IApp : public IFrameListener
{
public:
    virtual ~IApp() = 0;
};

inline IApp::~IApp() {}

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* IAPP_H */