#include "light.hpp"

Light::Light():
    intensity_{0},
    location_{0,0,0}
{
}

Light::Light(double intensity, point3D location):
    intensity_{intensity},
    location_{location}
{
}

Light::Light(const Light& rhs):
    location_(rhs.location_),
    intensity_(rhs.intensity_)
{
}

Light::~Light()
{
}

Light& Light::operator=(const Light& rhs)
{
    if (this == &rhs) {
        return *this;
    }

    location_ = rhs.location_;
    intensity_ = rhs.intensity_;
    return *this;
}

double Light::intensity(){
    return intensity_;
}

point3D Light::location(){
    return location_;
}
