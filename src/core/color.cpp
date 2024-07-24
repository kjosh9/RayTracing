#include "color.hpp"

Color::Color():
    red(0),
    green(0),
    blue(0)
{
}

Color::Color(int red, int green, int blue):
    red(red),
    green(green),
    blue(blue)
{
}

Color::Color(const Color& rhs) {
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
}

Color::~Color() {
}

bool Color::operator==(const Color& rhs) const {
    return rhs.red == red &&
        rhs.green == green &&
        rhs.blue == blue;
}

Color& Color::operator=(const Color& rhs) {
    if (this == &rhs) {
        return *this;   
    }

    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    return *this;
}

Color Color::operator-(const Color &rhs) {
    return Color(red - rhs.red, green - rhs.green, blue - rhs.blue);
}

Color Color::operator+(const Color &rhs) {
    return Color(red + rhs.red, green + rhs.green, blue + rhs.blue);
}

Color Color::operator*(const Color &rhs) {
    return Color(red * rhs.red, green * rhs.green, blue * rhs.blue);
}

Color Color::operator*(double scalar) {
    return Color(scalar*red, scalar*green, scalar*blue);
}