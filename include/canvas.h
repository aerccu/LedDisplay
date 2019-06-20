


#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>

namespace display
{
    class Canvas{
        virtual ~Canvas() {}

        virtual int width() const = 0;
        virtual int height() const = 0;

        virtual void setPix(int x, int y,
                            uint8_t r,
                            uint8_t g,
                            uint8_t b)
                            = 0;

        virtual void fill(uint8_t r,
                          uint8_t g,
                          uint8_t b)
                          = 0;

        virtual void clear() = 0;
        
    };   
}
#endif // CANVAS_H