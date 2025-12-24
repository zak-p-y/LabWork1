#ifndef BMPIMAGE_HPP
#define BMPIMAGE_HPP

#include "RasterImage.h"
#include "Image.h"
#include <filesystem>
#include <string>
#include <cstdint>

class BMP
{
private:
    static const std::string STANDARD;
    static const int HEADER_SIZE;
    static const int INFORMATION_SIZE;

    static int getPaddingSize(int imgWidth)
    {
        return (4 - (imgWidth * 3) % 4) % 4;
    }

public:
    static RasterImage load(const std::filesystem::path& imagePath);

    static void save(const std::filesystem::path& outputPath, const Image& image);
};

#pragma pack(push, 1)

struct BMPFileHeader
{
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
};

struct BMPInfoHeader
{
    uint32_t size;
    int32_t width;       
    int32_t height;      
    uint16_t planes;     
    uint16_t bpp;        
    uint32_t compression;
    uint32_t image_size; 
    int32_t  x_pixels_per_meter;
    int32_t  y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
}; // Total is  40 bytes

#pragma pack(pop)

#endif
