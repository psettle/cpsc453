#ifndef NAMEAPP_H
#define NAMEAPP_H

/**
file: NameApp.hpp
brief: Renders a name
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "IApp.hpp"
#include "IFrameDispatcher.hpp"
#include "IInputPoller.hpp"
#include "Polygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class NameApp : public IApp
{
public:
    NameApp(IFrameDispatcher* dispatcher, IInputPoller* input, const std::string& name);

    virtual ~NameApp();

    virtual void OnFrame();

    void CreateShapes();

    void DestroyShapes();

    void ProcessFontSelectionInput();

protected:
    IInputPoller*           pInputPollerM = nullptr;
    IFrameDispatcher*       pFrameDispatcherM = nullptr;
    std::vector<Polygon*>   activeShapesM;
    std::string             name;
    uint8                   activefont;

    KeyStateEnum          leftKeyCurrentStateM = KEY_STATE_RELEASE;
    KeyStateEnum          rightKeyCurrentStateM = KEY_STATE_RELEASE;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* NAMEAPP_H */