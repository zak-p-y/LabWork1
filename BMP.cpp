#include "BMP.hpp"
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

    // Skipping empty bytes up to start of raw pixel data.
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

    int imgWidth = image.getWidth();
   
