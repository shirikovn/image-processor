#include <stdexcept>

#include "edge_detection.h"

void EdgeDetection::Apply(PixelMatix& matrix, const std::vector<std::string>& params) {

    if (params.size() != 1) {
        throw FilterParamsError{"Edge Detection takes 1 param"};
    }

    double threshold = 0;

    try {
        threshold = stod(params[0]);
    } catch (const std::invalid_argument&) {
        throw FilterParamsError{
            "edge-detection takes only numbers as 1st param"};  // FIXME does not throw exception on 0.a
    } catch (const std::out_of_range&) {
        throw FilterParamsError{"Edge Detection: too big value"};
    }

    grayscale_.Apply(matrix, std::vector<std::string>{});

    std::vector<std::vector<Pixel>> new_matrix = matrix.matrix;

    for (size_t i = 0; i < matrix.matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.matrix[i].size(); ++j) {

            Pixel pixel = matrix.matrix[i][j];
            pixel *= 4;

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

            double value = std::max(0.0, std::min(1.0, pixel.red));

            if (value > threshold) {
                pixel.Set(1, 1, 1);
            } else {
                pixel.Set(0, 0, 0);
            }

            new_matrix[i][j] = pixel;
        }
    }

    matrix.matrix = std::move(new_matrix);
};
