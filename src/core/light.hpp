#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "point3d.hpp"

class Light {

public:
    Light();

    Light(double intensity, point3D location);

    Light(const Light& rhs);

    ~Light();

    Light& operator=(const Light& rhs);

    double intensity();

    point3D location();

private:
    double intensity_;
    point3D location_;
};

#endif
