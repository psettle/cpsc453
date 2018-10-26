/**
file: GlyphPolygon.cpp
brief:
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "GlyphPolygon.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

GlyphPolygon::GlyphPolygon(IFrameDispatcher* dispatcher, MyGlyph glyph, GLfloat scale, glm::vec3 offset)
{
    for (auto contour : glyph.contours)
    {
        for (auto curve : contour)
        {
            switch (curve.degree)
            {
            case 0:
            {
                glm::vec3 P0(0.0f);

                P0.x = curve.x[0];

                P0.y = curve.y[0];

                curves.push_back(new Bezier(dispatcher, P0, scale, offset));
            }
            break;
            case 1:
            {
                glm::vec3 P0(0.0f), P1(0.0f);

                P0.x = curve.x[0];
                P1.x = curve.x[1];

                P0.y = curve.y[0];
                P1.y = curve.y[1];

                curves.push_back(new Bezier(dispatcher, P0, P1, scale, offset));
            }
            break;
            case 2:
            {
                glm::vec3 P0(0.0f), P1(0.0f), P2(0.0f);

                P0.x = curve.x[0];
                P1.x = curve.x[1];
                P2.x = curve.x[2];

                P0.y = curve.y[0];
                P1.y = curve.y[1];
                P2.y = curve.y[2];

                curves.push_back(new Bezier(dispatcher, P0, P1, P2, scale, offset));
            }
            break;
            case 3:
            {
                glm::vec3 P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f);

                P0.x = curve.x[0];
                P1.x = curve.x[1];
                P2.x = curve.x[2];
                P3.x = curve.x[3];

                P0.y = curve.y[0];
                P1.y = curve.y[1];
                P2.y = curve.y[2];
                P3.y = curve.y[3];

                curves.push_back(new Bezier(dispatcher, P0, P1, P2, P3, scale, offset));
            }
            break;
            break;
            default:
                break;
            }
        }
    }


}

void GlyphPolygon::ApplyTranslation(const glm::vec3& translation)
{
    for (auto curve : curves)
    {
        curve->ApplyTranslation(translation);
    }
}

GlyphPolygon::~GlyphPolygon()
{
    for (auto curve : curves)
    {
        delete curve;
    }
}