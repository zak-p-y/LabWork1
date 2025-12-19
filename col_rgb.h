/*
* Pavel Zak
* st142062@student.spbu.ru
* LabWork1
*/

#ifndef COL_RGB_H
#define COL_RGB_H

#include <cstdint>

struct ColorRGB
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    // Required for dynamic initialization.
    ColorRGB() : red(0), green(0), blue(0) {}

    ColorRGB(uint8_t r, uint8_t g, uint8_t b)
        : red(r), green(g), blue(b) {}
};

#endif
