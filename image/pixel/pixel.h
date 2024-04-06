#pragma once

#include <cstdint>

namespace {
const double NORM_K = 255.0;
}

struct Pixel {
    Pixel();
    Pixel(double red, double green, double blue);
    void Set(double red, double green, double blue);

    Pixel operator*(double);
    void operator*=(double);
    void operator+=(const Pixel&);
    void operator-=(const Pixel&);

    double red, green, blue;
};

inline bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return static_cast<uint8_t>(lhs.red * NORM_K) == static_cast<uint8_t>(rhs.red * NORM_K) &&
           static_cast<uint8_t>(lhs.green * NORM_K) == static_cast<uint8_t>(rhs.green * NORM_K) &&
           static_cast<uint8_t>(lhs.blue * NORM_K) == static_cast<uint8_t>(rhs.blue * NORM_K);
}
