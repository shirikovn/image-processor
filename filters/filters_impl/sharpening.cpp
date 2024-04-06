#include "sharpening.h"
#include <iostream>

void Sharpening::Apply(PixelMatix& matrix, const std::vector<std::string>& params) {

    const double coef = 5;

    if (!params.empty()) {
        throw FilterParamsError{"sharpening doesn't take any params"};
    }

    std::vector<std::vector<Pixel>> new_matrix = matrix.matrix;

    for (size_t i = 0; i < matrix.matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.matrix[i].size(); ++j) {

            Pixel pixel = matrix.matrix[i][j];
            pixel *= coef;

            if (i != 0) {
                pixel -= matrix.matrix[i - 1][j];
            } else {
                pixel -= matrix.matrix[i][j];
            }

            if (i != matrix.matrix.size() - 1) {
                pixel -= matrix.matrix[i + 1][j];
            } else {
                pixel -= matrix.matrix[i][j];
            }

            if (j != 0) {
                pixel -= matrix.matrix[i][j - 1];
            } else {
                pixel -= matrix.matrix[i][j];
            }

            if (j != matrix.matrix[i].size() - 1) {
                pixel -= matrix.matrix[i][j + 1];
            } else {
                pixel -= matrix.matrix[i][j];
            }

            pixel.red = std::max(0.0, std::min(1.0, pixel.red));
            pixel.green = std::max(0.0, std::min(1.0, pixel.green));
            pixel.blue = std::max(0.0, std::min(1.0, pixel.blue));

            new_matrix[i][j] = pixel;
        }
    }

    matrix.matrix = std::move(new_matrix);
};
