/*
* Pavel Zak
* st142062@student.spbu.ru
LabWork1
*/

#include "BMP.h"
#include <fstream>

const std::string BMP::STANDARD = "BM";
const int BMP::HEADER_SIZE = 14;
const int BMP::INFORMATION_SIZE = 40;

RasterImage BMP::load(const std::filesystem::path& imagePath)
{
    std::ifstream inputFile(imagePath, std::ios::in | std::ios::binary);
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Could not open file: " + imagePath.string());
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    inputFile.read(reinterpret_cast<char*>(&fileHeader), HEADER_SIZE);
    inputFile.read(reinterpret_cast<char*>(&infoHeader), INFORMATION_SIZE);

    inputFile.seekg(fileHeader.data_offset, std::ios::beg);

    RasterImage resultImage(infoHeader.width, infoHeader.height);
    int paddingPerRow = BMP::getPaddingSize(infoHeader.width);

    for (int row = 0; row < infoHeader.height; ++row)
    {
        for (int col = 0; col < infoHeader.width; ++col)
        {
            uint8_t blue, green, red;
            inputFile.read(reinterpret_cast<char*>(&blue), 1);
            inputFile.read(reinterpret_cast<char*>(&green), 1);
            inputFile.read(reinterpret_cast<char*>(&red), 1);
            resultImage.setPixel(col, infoHeader.height - 1 - row, ColorRGB(red, green, blue));
        }
        inputFile.ignore(paddingPerRow);
    }

    return resultImage;
}

void BMP::save(const std::filesystem::path& outputPath, const Image& image)
{
    std::filesystem::path outputDir = outputPath.parent_path();
    if (!outputDir.empty() && !std::filesystem::exists(outputDir))
    {
        std::filesystem::create_directories(outputDir);
    }

    std::ofstream outputFile(outputPath, std::ios::out | std::ios::binary);
    if (!outputFile.is_open())
    {
        throw std::runtime_error("Could not open file for writing: " + outputPath.string());
    }

    int w = image.width();
    int h = image.height();
    int padding = getPaddingSize(w);

    BMPFileHeader fHeader;
    fHeader.file_type = 0x4D42; // "BM"
    fHeader.file_size = HEADER_SIZE + INFORMATION_SIZE + (3 * w + padding) * h;
    fHeader.reserved1 = 0;
    fHeader.reserved2 = 0;
    fHeader.data_offset = HEADER_SIZE + INFORMATION_SIZE;

    BMPInfoHeader iHeader;
    iHeader.size = INFORMATION_SIZE;
    iHeader.width = w;
    iHeader.height = h;
    iHeader.planes = 1;
    iHeader.bpp = 24;
    iHeader.compression = 0;
    iHeader.image_size = (3 * w + padding) * h;
    iHeader.x_pixels_per_meter = 0;
    iHeader.y_pixels_per_meter = 0;
    iHeader.colors_used = 0;
    iHeader.colors_important = 0;

    outputFile.write(reinterpret_cast<const char*>(&fHeader), HEADER_SIZE);
    outputFile.write(reinterpret_cast<const char*>(&iHeader), INFORMATION_SIZE);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            ColorRGB color = image.pixel(x, h - 1 - y);
            outputFile.put(static_cast<char>(color.blue));
            outputFile.put(static_cast<char>(color.green));
            outputFile.put(static_cast<char>(color.red));
        }
        for (int p = 0; p < padding; ++p)
        {
            outputFile.put(0);
        }
    }
} 
