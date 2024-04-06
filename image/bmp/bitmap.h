#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <stdexcept>

#include "pixel.h"

class FormatError : public std::runtime_error {
public:
    explicit FormatError(std::string msg) : runtime_error{msg} {};
};

struct BitmapHeader {
    uint16_t format;  // BP
    uint32_t size;
    uint32_t reserved;
    uint32_t offset;
};

struct BitmapInfo {
    uint32_t info_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t pixel_bit;    // should be 24
    uint32_t compression;  // always two-dimensional array
    uint32_t size_image;
    int32_t h_res;
    int32_t v_res;
    uint32_t color_in_table;
    uint32_t used_colors;
};

class PixelMatix {
public:
    PixelMatix();
    PixelMatix(int32_t height, int32_t width);

    std::vector<std::vector<Pixel>> matrix;
};

class BMPImage {
public:
    explicit BMPImage(std::string filepath);
    void Write(std::string filepath);

    PixelMatix matrix;

private:
    BitmapHeader header_;
    BitmapInfo info_;
};
