


#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <stdint.h>

#include "canvas.h"

namespace display
{
    struct Colour{
        Colour() : m_r(0), m_g(0), m_b(0) {}
        Colour(uint8_t r, uint8_t g, uint8_t b) : m_r(r), m_g(g), m_b(b) {}
        uint8_t m_r, m_g, m_b;
    };

    
    class Font{
        public:

        Font();
        ~Font();

        // bdf file loading
        bool loadFont(const char* fpath);

        int height() const { return font_h_; }

        int baseline() const { return baseline_; }

        int drawGlyph(Canvas* canvas, int x, int y, const Colour &colour,
                    const Colour* bg_colour,
                    uint32_t uc_codepoint) const;

        Font* createDerivedOutline() const;

        private:

        Font(const Font &s);

        struct Glyph;
        typedef std::map<uint32_t, Glyph*> CodepointGlyphMap;

        const Glyph* extractGlyph(uint32_t codepoint) const;

        int font_h_, baseline_;
        CodepointGlyphMap glyphs_;
    };


    int drawHorizontalText(Canvas* canvas, const Font &font, int x, int y,
                const Colour &colour, const Colour* bg_colour,
                const char* text, int kerning_distance = 0);

    int drawVerticalText(Canvas* canvas, const Font &font, int x, int y,
                const Colour &colour, const Colour* bg_colour,
                const char* text, int kerning_distance = 0);

    int drawLine(Canvas* canvas, int x0, int y0, 
                int x1, int y1, const Colour &colour);

    int drawCircle(Canvas* ccanvas, int x, int y,
                int radius, const Colour &colour);


}
#endif // GRAPHICS_H
