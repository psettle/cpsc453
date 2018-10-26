#ifndef STRINGPOLYGON_H
#define STRINGPOLYGON_H

/**
file: StringPolygon.hpp
brief:.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Polygon.hpp"

#include "GlyphPolygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class StringPolygon : public Polygon
{
public:
    StringPolygon(IFrameDispatcher* dispatcher, const std::string& string, const std::string& fontfile, GLfloat scale, glm::vec3& position);

    virtual void ApplyTranslation(const glm::vec3& translation);

    ~StringPolygon();

protected:
    std::vector<GlyphPolygon*> letters;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/

#endif /* STRINGPOLYGON_H */