#include <gtest/gtest.h>
#include <filesystem>
#include "../RasterImage.h"
#include "../img_processor.h"
#include "../BMP.h"
#include "../col_rgb.h"

using namespace std;


TEST(RasterImageTest, DimensionsBasic) {
    RasterImage img(4, 7);
    EXPECT_EQ(img.width(), 4);
    EXPECT_EQ(img.height(), 7);
}

TEST(RasterImageTest, DimensionsAnother) {
    RasterImage img(1, 1);
    EXPECT_EQ(img.width(), 1);
    EXPECT_EQ(img.height(), 1);
}

TEST(RasterImageTest, SetAndGetPixel) {
    RasterImage img(2, 2);
    img.setPixel(0, 1, ColorRGB(10, 20, 30));
    ColorRGB p = img.pixel(0, 1);
    EXPECT_EQ(p.red, 10);
    EXPECT_EQ(p.green, 20);
    EXPECT_EQ(p.blue, 30);
}

TEST(RasterImageTest, OverwritePixel) {
    RasterImage img(2, 2);
    img.setPixel(1, 1, ColorRGB(1, 2, 3));
    img.setPixel(1, 1, ColorRGB(7, 8, 9));
    ColorRGB p = img.pixel(1, 1);
    EXPECT_EQ(p.red, 7);
    EXPECT_EQ(p.green, 8);
    EXPECT_EQ(p.blue, 9);
}


TEST(ImageProcessorTest, RotateClockwiseSize) {
    RasterImage img(3, 5);
    RasterImage out = ImageProcessor::rotate90Clockwise(img);
    EXPECT_EQ(out.width(), 5);
    EXPECT_EQ(out.height(), 3);
}

TEST(ImageProcessorTest, RotateClockwisePixels) {
    RasterImage img(2, 3);
    img.setPixel(0, 0, ColorRGB(255, 0, 0));
    RasterImage out = ImageProcessor::rotate90Clockwise(img);
    EXPECT_EQ(out.pixel(2, 0).red, 255);
}


TEST(ImageProcessorTest, RotateAnticlockwiseSize) {
    RasterImage img(4, 6);
    RasterImage out = ImageProcessor::rotate90Antilockwise(img);
    EXPECT_EQ(out.width(), 6);
    EXPECT_EQ(out.height(), 4);
}



TEST(ImageProcessorTest, GaussianPreservesSize) {
    RasterImage img(8, 8);
    RasterImage out = ImageProcessor::applyGaussianFilter(img);
    EXPECT_EQ(out.width(), 8);
    EXPECT_EQ(out.height(), 8);
}

TEST(ImageProcessorTest, GaussianBlursCenter) {
    RasterImage img(3, 3);
    img.setPixel(1, 1, ColorRGB(255, 255, 255));
    RasterImage out = ImageProcessor::applyGaussianFilter(img);
    EXPECT_GT(out.pixel(1, 1).red, 0);
    EXPECT_LT(out.pixel(1, 1).red, 255);
}


TEST(BMPTest, SaveAndLoadPreservesPixels) {
    RasterImage img(3, 3);
    img.setPixel(0, 0, ColorRGB(10, 20, 30));
    img.setPixel(1, 1, ColorRGB(40, 50, 60));
    img.setPixel(2, 2, ColorRGB(70, 80, 90));

    filesystem::path path = filesystem::temp_directory_path() / "test.bmp";
    BMP::save(path, img);
    RasterImage loaded = BMP::load(path);

    ColorRGB p = loaded.pixel(1, 1);
    EXPECT_EQ(p.red, 40);
    EXPECT_EQ(p.green, 50);
    EXPECT_EQ(p.blue, 60);
}

TEST(BMPTest, LoadExistingFile) {
    RasterImage img = BMP::load("blue-bmp-24-bit.bmp");
    EXPECT_GT(img.width(), 0);
    EXPECT_GT(img.height(), 0);
}


TEST(BMPTest, PaddingWidthOne) {
    RasterImage img(1, 4);
    img.setPixel(0, 2, ColorRGB(123, 45, 67));

    filesystem::path path = filesystem::temp_directory_path() / "pad1.bmp";
    BMP::save(path, img);
    RasterImage loaded = BMP::load(path);

    ColorRGB p = loaded.pixel(0, 2);
    EXPECT_EQ(p.red, 123);
    EXPECT_EQ(p.green, 45);
    EXPECT_EQ(p.blue, 67);
}

TEST(BMPTest, PaddingWidthThree) {
    RasterImage img(3, 2);
    img.setPixel(2, 1, ColorRGB(9, 8, 7));

    filesystem::path path = filesystem::temp_directory_path() / "pad3.bmp";
    BMP::save(path, img);
    RasterImage loaded = BMP::load(path);

    ColorRGB p = loaded.pixel(2, 1);
    EXPECT_EQ(p.red, 9);
    EXPECT_EQ(p.green, 8);
    EXPECT_EQ(p.blue, 7);
}
