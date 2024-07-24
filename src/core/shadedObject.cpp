#include "shadedObject.hpp"

ShadedObject::ShadedObject():
    lambert_{0},
    center_{0,0,0},
    color_{Color()}
{
}

ShadedObject::ShadedObject(double lambert, point3D location, Color color):
    lambert_{lambert},
    center_{location},
    color_{color}
{
}

ShadedObject::ShadedObject(const ShadedObject& rhs):
    lambert_{rhs.lambert_},
    center_{rhs.center_},
    color_{color_}
{
}

ShadedObject::~ShadedObject()
{
}

ShadedObject& ShadedObject::operator=(const ShadedObject& rhs)
{
    if(this == &rhs) {
        return *this;
    }

    lambert_ = rhs.lambert_;
    center_ = rhs.center_;
    color_ = rhs.color_;
    return *this;
}

double ShadedObject::lambert(){
    return lambert_;
}

point3D ShadedObject::center(){
    return center_;
}

Color ShadedObject::color(){
    return color_;
}
