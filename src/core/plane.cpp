#include "plane.hpp"
#include <cmath>

Plane::Plane() :
    ShadedObject(){
}

Plane::Plane(double lambert,
             point3D location,
             Color color,
             point3D normal) :
    ShadedObject(lambert, location, color),
    normal_{normal}
{
}

Plane::Plane(const Plane& rhs):
    ShadedObject(rhs.lambert_, rhs.center_, rhs.color_),
    normal_(rhs.normal_)
{    
}

Plane::~Plane()
{
}

Plane& Plane::operator=(const Plane& rhs)
{
    if(this == &rhs) {
        return *this;
    }

    lambert_ = rhs.lambert_;
    center_ = rhs.center_;
    color_ = rhs.color_;
    normal_ = rhs.normal_;
    return *this;
}

point3D Plane::normal(){
    return normal_;
}

bool Plane::intersects(point3D start,
                       point3D direction,
                       point3D &intersection,
                       point3D &normal){

    auto min_mag = 0.0001f;

    double mag = normal_.dot_product(direction);
    if(std::abs(mag) > min_mag) {
        point3D distance = center_ - start;
        double length = distance.dot_product(normal_)/mag;
        intersection = start + direction * length;
        
        if (mag > 0)
            normal = normal_ * -1;
        else
            normal = normal_;

        return length > min_mag;
    }
    return false;
}
