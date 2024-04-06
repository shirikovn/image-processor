#include <algorithm>
#include <stdexcept>

#include "crop.h"

void Crop::Apply(PixelMatix& matrix, const std::vector<std::string>& params) {

    if (params.size() != 2) {
        throw FilterParamsError{"crop takes 2 params"};
    }

    size_t width = 0;
    size_t length = 0;

    try {
        width = std::stoi(params[0]);
        length = std::stoi(params[1]);
    } catch (const std::invalid_argument& e) {
        throw FilterParamsError{"crop takes only natural params"};
    } catch (const std::out_of_range& e) {
        throw FilterParamsError{"too big params for crop"};
    }

    if (width <= 0 || length <= 0) {
        throw FilterParamsError{"crop takes only natural params"};
    }

    width = std::min(width, matrix.matrix[0].size());
    length = std::min(length, matrix.matrix.size());

    std::reverse(matrix.matrix.begin(), matrix.matrix.end());
    matrix.matrix.resize(length);
    std::reverse(matrix.matrix.begin(), matrix.matrix.end());

    for (size_t i = 0; i < matrix.matrix.size(); ++i) {
        matrix.matrix[i].resize(width);
    }
};
