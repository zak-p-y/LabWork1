#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include "col_rgb.h"

class Image
{
public:
    virtual ~Image() = default;

    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual ColorRGB pixel(int x, int y) const = 0;

    virtual void setPixel(int x, int y, ColorRGB color) = 0;
};

#endif
