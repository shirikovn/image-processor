#include "bitmap.h"
#include <fstream>

const double NORMALIZE_K = 255.0;

PixelMatix::PixelMatix() {
}

PixelMatix::PixelMatix(int32_t height, int32_t width) {
    matrix = std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width));
};

BMPImage::BMPImage(std::string filepath) {

    std::ifstream istream(filepath, std::ios::in | std::ios::binary);
    istream.exceptions(std::ofstream::badbit | std::ofstream::failbit);

    // istream.read(reinterpret_cast<char*>(&header), sizeof header); - doesn't work due paddings

    istream.read(reinterpret_cast<char*>(&header_.format), sizeof header_.format);
    istream.read(reinterpret_cast<char*>(&header_.size), sizeof header_.size);
    istream.read(reinterpret_cast<char*>(&header_.reserved), sizeof header_.reserved);
    istream.read(reinterpret_cast<char*>(&header_.offset), sizeof header_.offset);

    const uint32_t bpsigntatur_e1 = 19778;
    const uint32_t bpsigntatur_e2 = 16973;

    if (header_.format != bpsigntatur_e1 && header_.format != bpsigntatur_e2) {
        throw FormatError{"Given file is not bmp. Program works only with bmp."};
    }

    istream.read(reinterpret_cast<char*>(&info_), sizeof info_);

    const uint16_t req_bits_per_pixel = 24;

    if (info_.pixel_bit != req_bits_per_pixel) {
        throw FormatError{"Support only 24 bit bmp."};
    }

    if (info_.compression != 0) {
        throw FormatError{"Do not support compressed images."};
    }

    matrix = PixelMatix(info_.height, info_.width);

    istream.seekg(header_.offset);

    for (int32_t rowi = 0; rowi < abs(info_.height); ++rowi) {
        std::vector<Pixel> row;

        int32_t real_rowi = rowi;

        if (info_.height < 0) {
            real_rowi = abs(info_.height) - rowi - 1;
        }

        for (size_t coli = 0; coli < info_.width; ++coli) {

            uint8_t blue = istream.get();
            uint8_t green = istream.get();
            uint8_t red = istream.get();

            double dred = static_cast<double>(red) / NORMALIZE_K;
            double dgreen = static_cast<double>(green) / NORMALIZE_K;
            double dblue = static_cast<double>(blue) / NORMALIZE_K;

            matrix.matrix[real_rowi][coli] = Pixel(dred, dgreen, dblue);
        }

        istream.seekg(info_.width % 4, std::ios::cur);
    }

    istream.close();
};

void BMPImage::Write(std::string filepath) {
    std::ofstream ofstream(filepath.c_str(), std::ios::out | std::ios::binary);
    ofstream.exceptions(std::ofstream::badbit | std::ofstream::failbit);

    // update header/info before write
    header_.size = header_.offset + (matrix.matrix[0].size() * 3 + matrix.matrix[0].size() % 4) * matrix.matrix.size();

    info_.width = static_cast<int32_t>(matrix.matrix[0].size());
    info_.height = static_cast<int32_t>(matrix.matrix.size());

    ofstream.write(reinterpret_cast<char*>(&header_.format), sizeof(header_.format));
    ofstream.write(reinterpret_cast<char*>(&header_.size), sizeof(header_.size));
    ofstream.write(reinterpret_cast<char*>(&header_.reserved), sizeof(header_.reserved));
    ofstream.write(reinterpret_cast<char*>(&header_.offset), sizeof(header_.offset));

    info_.height = abs(info_.height);

    ofstream.write(reinterpret_cast<char*>(&info_), sizeof(info_));

    for (int32_t rowi = 0; rowi < matrix.matrix.size(); ++rowi) {
        const std::vector<Pixel>& row = matrix.matrix[rowi];

        for (int coli = 0; coli < row.size(); coli++) {
            const Pixel& pixel = row[coli];

            uint8_t red = static_cast<uint8_t>(pixel.red * NORMALIZE_K);
            uint8_t green = static_cast<uint8_t>(pixel.green * NORMALIZE_K);
            uint8_t blue = static_cast<uint8_t>(pixel.blue * NORMALIZE_K);

            ofstream.put(static_cast<char>(blue));
            ofstream.put(static_cast<char>(green));
            ofstream.put(static_cast<char>(red));
        }

        for (int i = 0; i < row.size() % 4; i++) {
            ofstream.put(0);
        }
    }

    ofstream.close();
};
