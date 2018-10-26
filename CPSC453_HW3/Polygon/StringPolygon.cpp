/**
file: StringPolygon.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "StringPolygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

StringPolygon::StringPolygon(IFrameDispatcher* dispatcher, const std::string& string, const std::string& fontfile, GLfloat scale, glm::vec3& position)
{
    GlyphExtractor ex;

    glm::vec3 offset = position;

    ex.LoadFontFile(fontfile);

    for (auto letter : string)
    {
        letters.push_back(new GlyphPolygon(dispatcher, ex.ExtractGlyph(letter), scale, offset));

        offset.x += ex.ExtractGlyph(letter).advance;
    }
}

void StringPolygon::ApplyTranslation(const glm::vec3& translation)
{
    for (auto& glyph : letters)
    {
        glyph->ApplyTranslation(translation);
    }
}

StringPolygon::~StringPolygon()
{
    for (auto& glyph : letters)
    {
        delete glyph;
    }
}