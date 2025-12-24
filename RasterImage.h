#ifndef RASTER_IMAGE_HPP
#define RASTER_IMAGE_HPP

#include "Image.h"
#include "col_rgb.h"
#include <vector>

class RasterImage : public Image
{
private:
    int w;
    int h;
    std::vector<ColorRGB> pixels;

public:
    RasterImage(int width, int height)
        : w(width), h(height), pixels(width * height) {}

    int width() const override
    {
        return w;
    }

    int height() const override
    {
        return h;
    }

    ColorRGB pixel(int x, int y) const override
    {
        return pixels[y * w + x];
    }

    void setPixel(int x, int y, ColorRGB color) override
    {
        pixels[y * w + x] = color;
    }
};

#endif
