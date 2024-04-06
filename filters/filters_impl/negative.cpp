#include "negative.h"

void Negative::Apply(PixelMatix& matrix, const std::vector<std::string>& params) {
    if (!params.empty()) {
        throw FilterParamsError{"negative doesn't take any params"};
    }

    for (size_t i = 0; i < matrix.matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.matrix[i].size(); ++j) {
            Pixel pixel = matrix.matrix[i][j];
            matrix.matrix[i][j].Set(1 - pixel.red, 1 - pixel.green, 1 - pixel.blue);
        }
    }
};
