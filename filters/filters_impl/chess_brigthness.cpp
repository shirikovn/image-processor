#include "chess_brigthness.h"

#include <stdexcept>
#include <algorithm>
#include <iostream>

void ChessBrightness::Apply(PixelMatix& matrix, const std::vector<std::string>& params) {
    if (params.size() != 2) {
        throw FilterParamsError{"negative doesn't take any params"};
    }

    double k = 0;

    try {
        k = stod(params[0]);
    } catch (const std::invalid_argument&) {
        throw FilterParamsError{"chess-brightness takes only real numbers as 1st param"};
    } catch (const std::out_of_range&) {
        throw FilterParamsError{"too big value for chess-brightness"};
    }

    if (k > 1 || k < -1) {
        throw FilterParamsError{"chess-brightness takes only numbers from -1 to 1 as first param"};
    }

    size_t size_of_cell = 0;

    try {
        size_of_cell = std::stoi(params[1]);
    } catch (const std::invalid_argument& e) {
        throw FilterParamsError{"chess-brightness takes only natural numbers as second param"};
    } catch (const std::out_of_range& e) {
        throw FilterParamsError{"too big params for chess-brightness"};
    }

    if (size_of_cell <= 0) {
        throw FilterParamsError{"chess-brightness takes only natural numbers as second param"};
    }

    for (size_t i = 0; i < matrix.matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.matrix[0].size(); ++j) {
            if (((matrix.matrix.size() - i - 1) / size_of_cell + j / size_of_cell) % 2 == 0) {

                Pixel& pixel = matrix.matrix[i][j];

                pixel.red += k;
                pixel.green += k;
                pixel.blue += k;

                pixel.red = std::max(0.0, std::min(1.0, pixel.red));
                pixel.green = std::max(0.0, std::min(1.0, pixel.green));
                pixel.blue = std::max(0.0, std::min(1.0, pixel.blue));
            }
        }
    }
};
