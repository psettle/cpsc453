/**
file: StbImage.cpp
brief: Wrapper for stb image libray
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "StbImage.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

StbImage::StbImage(std::string const & pathName, uint8 desiredChannels)
{
    imageDataM = stbi_load(pathName.c_str(), &xsizeM, &ysizeM, &compCountM, desiredChannels);
    compCountM = desiredChannels;
}

stbi_uc const * StbImage::ReadImageData() const
{
    return imageDataM;
}

uint32 StbImage::ReadWidth() const
{
    return xsizeM;
}

uint32 StbImage::ReadHeight() const
{
    return ysizeM;
}

uint32 StbImage::ReadComponents() const
{
    return compCountM;
}

StbImage::~StbImage()
{
    stbi_image_free(imageDataM);
}