/*
* Pavel Zak
* st142062@student.spbu.ru
LabWork1
*/


#ifndef IMG_PROCESSOR_HPP
#define IMG_PROCESSOR_HPP

#include "col_rgb.h"
#include "Image.h"
#include "RasterImage.h"

class ImageProcessor
{
private:
    static ColorRGB fetchClampedPixel(const Image&, int, int);
public:
    static RasterImage applyGaussianFilter(const Image& image);
    static RasterImage rotate90Clockwise(const Image& image);
    static RasterImage rotate90Antilockwise(const Image& image);
};

#endif
