/**
file: AppManager.cpp
brief: Top level app manager for cpsc453 HW1
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include <sstream> 

#include "AppManager.hpp"
#include "SquareDiamondApp.hpp"
#include "SpiralApp.hpp"
#include "SierpinskiApp.hpp"
#include "SierpinskiDotsApp.hpp"
#include "BarnsleyFernApp.hpp"
#include "HilbertSpaceCurveApp.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

AppManager::AppManager(IFrameDispatcher* dispatcher, IInputPoller* poller)
    : pFrameDispatcherM(dispatcher), pInputPollerM(poller)
{
    pFrameDispatcherM->RegisterFrameListener(this);
    SetCurrentApp();
}

void AppManager::OnFrame()
{
    ProcessNumberInput();
    ProcessAppSelectionInput();
}

void AppManager::ProcessNumberInput()
{
    switch (numberReaderStateM)
    {
    case NUMBER_READER_STATE_WAIT_FOR_KEY_PRESS:
        /* Poll all the keys we care about and change state if required: */
        for (uint16 i = GLFW_KEY_0; i <= GLFW_KEY_9; ++i)
        {
            if (KEY_STATE_PRESS == pInputPollerM->GetKey(i))
            {
                numberReaderStateM = NUMBER_READER_STATE_WAIT_FOR_KEY_RELEASE;
                glfwPressedKeyM = i;
                break;
            }
        }

        if (KEY_STATE_PRESS == pInputPollerM->GetKey(GLFW_KEY_ENTER))
        {
            numberReaderStateM = NUMBER_READER_STATE_WAIT_FOR_KEY_RELEASE;
            glfwPressedKeyM = GLFW_KEY_ENTER;
            break;
        }

        break;
    case NUMBER_READER_STATE_WAIT_FOR_KEY_RELEASE:
        /* See if the pressed key has been released, then process. */
        if (KEY_STATE_RELEASE == pInputPollerM->GetKey(glfwPressedKeyM))
        {
            if (GLFW_KEY_ENTER == glfwPressedKeyM)
            {
                uint32 number = 0; /* uint32 is safe because only + inputs are possible. */
                std::stringstream reader(pressedKeyBufferM);

                reader >> number;

                if (number > 0)
                {
                    pActiveAppM->SetNumber(number);
                    std::cout << number << std::endl;
                }
                else if (pressedKeyBufferM == "0")
                {
                    pActiveAppM->SetNumber(0);
                    std::cout << 0 << std::endl;
                }
                else
                {
                    std::cout << "Invalid input, try again." << std::endl;
                }

                pressedKeyBufferM = "";
            }
            else
            {
                pressedKeyBufferM += ('0' + glfwPressedKeyM - GLFW_KEY_0);
            }

            glfwPressedKeyM = GLFW_KEY_UNKNOWN;
            numberReaderStateM = NUMBER_READER_STATE_WAIT_FOR_KEY_PRESS;
        }
        break;
    }
}

void AppManager::ProcessAppSelectionInput()
{
    KeyStateEnum up_state = pInputPollerM->GetKey(GLFW_KEY_UP);
    KeyStateEnum down_state = pInputPollerM->GetKey(GLFW_KEY_DOWN);

    if (up_state != upKeyCurrentStateM)
    {
        if (up_state == KEY_STATE_RELEASE)
        {
            IncrementActiveApp();
        }

        upKeyCurrentStateM = up_state;
    }

    if (down_state != downKeyCurrentStateM)
    {
        if (down_state == KEY_STATE_RELEASE)
        {
            DecrementActiveApp();
        }

        downKeyCurrentStateM = down_state;
    }
}

void AppManager::IncrementActiveApp()
{
    switch (activeAppEnumM)
    {
    case ACTIVE_APP_NESTED_SQUARES:
        activeAppEnumM = ACTIVE_APP_SPIRAL;
        break;
    case ACTIVE_APP_SPIRAL:
        activeAppEnumM = ACTIVE_APP_SIERPINSKI;
        break;
    case ACTIVE_APP_SIERPINSKI:
        activeAppEnumM = ACTIVE_APP_SIERPINSKIDOTS;
        break;
    case ACTIVE_APP_SIERPINSKIDOTS:
        activeAppEnumM = ACTIVE_APP_BARNSLEYFERN;
        break;
    case ACTIVE_APP_BARNSLEYFERN:
        activeAppEnumM = ACTIVE_APP_HILBERTSPACECURVE;
        break;
    case ACTIVE_APP_HILBERTSPACECURVE:
        activeAppEnumM = ACTIVE_APP_NESTED_SQUARES;
        break;
    default:
        break;
    }
    
    SetCurrentApp();
}
void AppManager::DecrementActiveApp()
{
    switch (activeAppEnumM)
    {
    case ACTIVE_APP_NESTED_SQUARES:
        activeAppEnumM = ACTIVE_APP_HILBERTSPACECURVE;
        break;
    case ACTIVE_APP_SPIRAL:
        activeAppEnumM = ACTIVE_APP_NESTED_SQUARES;
        break;
    case ACTIVE_APP_SIERPINSKI:
        activeAppEnumM = ACTIVE_APP_SPIRAL;
        break;
    case ACTIVE_APP_SIERPINSKIDOTS:
        activeAppEnumM = ACTIVE_APP_SIERPINSKI;
        break;
    case ACTIVE_APP_BARNSLEYFERN:
        activeAppEnumM = ACTIVE_APP_SIERPINSKIDOTS;
        break;
    case ACTIVE_APP_HILBERTSPACECURVE:
        activeAppEnumM = ACTIVE_APP_BARNSLEYFERN;
        break;
    default:
        break;
    }

    SetCurrentApp();
}

void AppManager::SetCurrentApp()
{
    delete pActiveAppM;

    switch (activeAppEnumM)
    {
    case ACTIVE_APP_NESTED_SQUARES:
        pActiveAppM = new SquareDiamondApp(pFrameDispatcherM);
        break;
    case ACTIVE_APP_SPIRAL:
        pActiveAppM = new SpiralApp(pFrameDispatcherM);
        break;
    case ACTIVE_APP_SIERPINSKI:
        pActiveAppM = new SierpinskiApp(pFrameDispatcherM);
        break;
    case ACTIVE_APP_SIERPINSKIDOTS:
        pActiveAppM = new SierpinskiDotsApp(pFrameDispatcherM);
        break;
    case ACTIVE_APP_BARNSLEYFERN:
        pActiveAppM = new BarnsleyFernApp(pFrameDispatcherM);
        break;
    case ACTIVE_APP_HILBERTSPACECURVE:
        pActiveAppM = new HilbertSpaceCurveApp(pFrameDispatcherM);
        break;
    default:
        break;
    }
}

AppManager::~AppManager()
{
    delete pActiveAppM;
    pFrameDispatcherM->UnregisterFrameListener(this);
}