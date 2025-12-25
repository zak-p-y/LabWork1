/*
* Pavel Zak
* st142062@student.spbu.ru
LabWork1
*/

#include <filesystem>
#include <iostream>
#include "BMP.h"
#include "RasterImage.h"
#include "img_processor.h"

static std::string getInput(const char* msg)
{
    std::cout << msg;
    std::string val;
    std::getline(std::cin, val);
    return val;
}

int main()
{
    std::filesystem::path srcPath = getInput("Enter BMP image path (Linux style): ");
    std::filesystem::path outDir = "output_images";

    RasterImage origImg = BMP::load(srcPath);
    BMP::save(outDir / "default.bmp", origImg);

    RasterImage gaussImg = ImageProcessor::applyGaussianFilter(origImg);
    BMP::save(outDir / "gaussian_filtered.bmp", gaussImg);

    RasterImage cwImg = ImageProcessor::rotate90Clockwise(origImg);
    BMP::save(outDir / "rotated_clockwise.bmp", cwImg);

    RasterImage ccwImg = ImageProcessor::rotate90Antilockwise(origImg);
    BMP::save(outDir / "rotated_anticlockwise.bmp", ccwImg);

    return 0;
}
