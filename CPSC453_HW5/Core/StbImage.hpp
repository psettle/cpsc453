#ifndef STBIMAGE_H
#define STBIMAGE_H

/**
file: StbImage.hpp
brief: Wrapper for StbImage library
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
class StbImage
{
public:

    StbImage(std::string const & pathName, uint8 desiredChannels);

    stbi_uc const * ReadImageData() const;

    uint32 ReadWidth() const;

    uint32 ReadHeight() const;

    uint32 ReadComponents() const;

    ~StbImage();

protected:

    int xsizeM;
    int ysizeM;
    int compCountM;
    stbi_uc* imageDataM;
};
/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* STBIMAGE_H */