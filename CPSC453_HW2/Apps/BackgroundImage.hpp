#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H

/**
file: BackgroundImage.hpp
brief: Shows an openGL 2D image.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Common.hpp"
#include "IFrameListener.hpp"
#include "IFrameDispatcher.hpp"
#include "Shader.hpp"
#include "StbImage.hpp"
#include "Texture.hpp"
#include "Image.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class BackgroundImage : public Image
{
public:
    BackgroundImage(std::string const & imagePath, IFrameDispatcher* dispatcher)
        : Image::Image(imagePath, dispatcher)
    {
        /* Move to front of render queue. */
        pFrameDispatcherM->UnregisterFrameListener(this);
        pFrameDispatcherM->RegisterFrameListener(this, true);
    }

protected:
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* BACKGROUNDIMAGE_H */