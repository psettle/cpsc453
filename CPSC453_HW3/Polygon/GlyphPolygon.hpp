#ifndef GLYPHPOLYGON_H
#define GLYPHPOLYGON_H

/**
file: GlyphPolygon.hpp
brief:.
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "Polygon.hpp"
#include "Bezier.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

class GlyphPolygon : public Polygon
{
public:
    GlyphPolygon(IFrameDispatcher* dispatcher, MyGlyph glyph, GLfloat scale, glm::vec3 offset);

    virtual void ApplyTranslation(const glm::vec3& translation);

    ~GlyphPolygon();
protected:
    std::vector<Bezier*> curves;
};

/**********************************************************
                       DEFINITIONS
**********************************************************/



#endif /* GLYPHPOLYGON_H */