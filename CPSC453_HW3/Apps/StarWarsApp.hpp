#ifndef STARWARSAPP_H
#define STARWARSAPP_H

/**
file: StarWarsApp.hpp
brief: Rebellions are built on hope
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

class StarWarsApp : public IApp
{
public:
    StarWarsApp(IFrameDispatcher* dispatcher, IInputPoller* input);

    virtual ~StarWarsApp();

    virtual void OnFrame();

    void CreateShapes();

    void DestroyShapes();

    void ProcessFontSelectionInput();
    void ProcessScrollRateInput();

protected:  
    IFrameDispatcher*       pFrameDispatcherM;
    IInputPoller*           pInputPollerM;
    std::vector<Polygon*>   activeShapesM;
    std::string             name;
    uint8                   activefont;
    glm::vec3               translation;
    GLdouble                oldTime;
    GLdouble                scrollRateM;

    KeyStateEnum          leftKeyCurrentStateM = KEY_STATE_RELEASE;
    KeyStateEnum          rightKeyCurrentStateM = KEY_STATE_RELEASE;
    KeyStateEnum          aKeyCurrentStateM = KEY_STATE_RELEASE;
    KeyStateEnum          dKeyCurrentStateM = KEY_STATE_RELEASE;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* STARWARSAPP_H */
