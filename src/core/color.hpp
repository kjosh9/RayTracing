#ifndef COLOR_HPP
#define COLOR_HPP


class Color
{
public:
    Color();
    Color(int red, int green, int blue);
    Color(const Color& rhs);
    ~Color();

    bool operator==(const Color& rhs) const;
    Color& operator=(const Color& rhs);

    Color operator-(const Color &rhs);
    Color operator+(const Color &rhs);
    Color operator*(const Color &rhs);
    Color operator*(double scalar);

    int red;
    int green;
    int blue;
};

#endif // COLOR_HPP
