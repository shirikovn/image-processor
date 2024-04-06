#include "grayscale.h"

void Grayscale::Apply(PixelMatix& matrix, const std::vector<std::string>& params) {

    const double coef_red = 0.299;
    const double coef_green = 0.587;
    const double coef_blue = 0.114;

    if (!params.empty()) {
        throw FilterParamsError{"grayscale doesn't take any params"};
    }

    for (size_t i = 0; i < matrix.matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.matrix[i].size(); ++j) {
            double grey_value = std::min(coef_red * matrix.matrix[i][j].red + coef_green * matrix.matrix[i][j].green +
                                             coef_blue * matrix.matrix[i][j].blue,
                                         1.0);

            matrix.matrix[i][j].Set(grey_value, grey_value, grey_value);
        }
    }
};
