/*
* Pavel Zak
* st142062@student.spbu.ru
LabWork1
*/
#include "img_processor.h"
#include <algorithm>
#include <cstdint>

ColorRGB ImageProcessor::fetchClampedPixel(const Image& img, int x, int y)
{
    int cx = std::max(0, std::min(x, img.width() - 1));
    int cy = std::max(0, std::min(y, img.height() - 1));
    return img.pixel(cx, cy);
}

RasterImage ImageProcessor::applyGaussianFilter(const Image& img)
{
    const float kernel[3][3] =
    {
        {1 / 16.0f, 2 / 16.0f, 1 / 16.0f},
        {2 / 16.0f, 4 / 16.0f, 2 / 16.0f},
        {1 / 16.0f, 2 / 16.0f, 1 / 16.0f}
    };

    int w = img.width();
    int h = img.height();
    RasterImage output(w, h);

    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            float r_acc = 0.0f;
            float g_acc = 0.0f;
            float b_acc = 0.0f;

            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {
                 ColorRGB px = fetchClampedPixel(img, i + dx, j + dy);
                 float k = kernel[dy + 1][dx + 1];
                 r_acc += static_cast<float>(px.red) * k;
                 g_acc += static_cast<float>(px.green) * k;
                 b_acc += static_cast<float>(px.blue) * k;
                }
            }

            uint8_t r = static_cast<uint8_t>(std::min(std::max(static_cast<int>(r_acc), 0), 255));
            uint8_t g = static_cast<uint8_t>(std::min(std::max(static_cast<int>(g_acc), 0), 255));
            uint8_t b = static_cast<uint8_t>(std::min(std::max(static_cast<int>(b_acc), 0), 255));
            output.setPixel(i, j, ColorRGB(r, g, b));
        }
    }

    return output;
}

RasterImage ImageProcessor::rotate90Clockwise(const Image& img)
{
    int w = img.width();
    int h = img.height();
    RasterImage output(h, w);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            output.setPixel(h - 1 - y, x, img.pixel(x, y));
        }
    }

    return output;
}

RasterImage ImageProcessor::rotate90Antilockwise(const Image& img)
{
    int w = img.width();
    int h = img.height();
    RasterImage output(h, w);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            output.setPixel(y, w - 1 - x, img.pixel(x, y));
        }
    }

    return output;
}
