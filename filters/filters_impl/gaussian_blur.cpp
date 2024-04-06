#include "gaussian_blur.h"
#include <numbers>
#include <cmath>
#include <algorithm>
#include <stdexcept>

void GaussianBlur::Apply(PixelMatix& matrix, const std::vector<std::string>& params) {

    if (params.size() != 1) {
        throw FilterParamsError{"gaussian blur takes 1 param"};
    }

    double sigma = 0;

    try {
        sigma = stod(params[0]);
    } catch (const std::invalid_argument&) {
        throw FilterParamsError{
            "gaussian blur takes only numbers as 1st param"};  // FIXME does not throw exception on 0.a
    } catch (const std::out_of_range&) {
        throw FilterParamsError{"too big value for gaussian blur"};
    }

    std::vector<std::vector<Pixel>> new_matrix = matrix.matrix;

    const double k2 = 2.0;

    const double mn = (1.0 / std::sqrt(k2 * std::numbers::pi * std::pow(sigma, k2)));
    const double st_mn = -(1 / (2 * std::pow(sigma, k2)));

    int64_t diff = static_cast<int64_t>(std::ceil(3 * sigma));

    std::vector<double> koefs(diff * 2 + 1);

    for (int64_t i = 0; i < diff * 2 + 1; ++i) {
        double k = mn * std::pow(std::numbers::e, std::pow(std::abs(diff - i), 2) * st_mn);
        koefs[i] = k;
    }

    for (int64_t i = 0; i < matrix.matrix.size(); ++i) {
        for (int64_t j = 0; j < matrix.matrix[i].size(); ++j) {

            Pixel pixel{};

            for (int64_t x = i - diff; x <= i + diff; ++x) {

                int64_t x_in_matrix =
                    std::min(static_cast<int64_t>(matrix.matrix.size() - 1), std::max(static_cast<int64_t>(0), x));

                pixel.red += matrix.matrix[x_in_matrix][j].red * koefs[x + diff - i];
                pixel.green += matrix.matrix[x_in_matrix][j].green * koefs[x + diff - i];
                pixel.blue += matrix.matrix[x_in_matrix][j].blue * koefs[x + diff - i];
            }

            pixel.red = std::max(0.0, std::min(1.0, pixel.red));
            pixel.green = std::max(0.0, std::min(1.0, pixel.green));
            pixel.blue = std::max(0.0, std::min(1.0, pixel.blue));

            new_matrix[i][j] = pixel;
        }
    }

    matrix.matrix = new_matrix;

    for (int64_t i = 0; i < matrix.matrix.size(); ++i) {
        for (int64_t j = 0; j < matrix.matrix[i].size(); ++j) {

            Pixel pixel{};

            for (int64_t y = j - diff; y <= j + diff; ++y) {

                int64_t y_in_matrix =
                    std::min(static_cast<int64_t>(matrix.matrix[0].size() - 1), std::max(static_cast<int64_t>(0), y));

                pixel.red += matrix.matrix[i][y_in_matrix].red * koefs[y + diff - j];
                pixel.green += matrix.matrix[i][y_in_matrix].green * koefs[y + diff - j];
                pixel.blue += matrix.matrix[i][y_in_matrix].blue * koefs[y + diff - j];
            }

            pixel.red = std::max(0.0, std::min(1.0, pixel.red));
            pixel.green = std::max(0.0, std::min(1.0, pixel.green));
            pixel.blue = std::max(0.0, std::min(1.0, pixel.blue));

            new_matrix[i][j] = pixel;
        }
    }

    matrix.matrix = std::move(new_matrix);
};
