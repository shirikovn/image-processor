#include "pixel.h"

Pixel::Pixel() : red{0}, green{0}, blue{0} {
}

Pixel::Pixel(double red, double green, double blue) : red{red}, green{green}, blue{blue} {
}

void Pixel::Set(double red, double green, double blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Pixel Pixel::operator*(double mult) {
    Pixel pixel_copy = *this;
    pixel_copy.red *= mult;
    pixel_copy.green *= mult;
    pixel_copy.blue *= mult;

    return pixel_copy;
}

void Pixel::operator*=(double mult) {
    red *= mult;
    green *= mult;
    blue *= mult;
}

void Pixel::operator+=(const Pixel& rhs) {
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
}

void Pixel::operator-=(const Pixel& rhs) {
    red -= rhs.red;
    green -= rhs.green;
    blue -= rhs.blue;
}
