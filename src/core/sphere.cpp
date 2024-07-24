#include <cmath>
#include "sphere.hpp"

Sphere::Sphere() :
    ShadedObject()
{
}

Sphere::Sphere(double lambert, point3D location, Color color, double radius):
    ShadedObject(lambert, location, color),
    radius_{radius}
{
}

Sphere::Sphere(const Sphere& rhs):
    ShadedObject(rhs.lambert_, rhs.center_, rhs.color_),
    radius_{rhs.radius_}
{
}

Sphere::~Sphere()
{
}

Sphere& Sphere::operator=(const Sphere& rhs)
{
    if(this == &rhs) {
        return *this;
    }

    lambert_ = rhs.lambert_;
    center_ = rhs.center_;
    color_ = rhs.color_;
    radius_ = rhs.radius_;
    return *this;
}

double Sphere::radius(){
    return radius_;
}

bool Sphere::intersects(const point3D start, const point3D direction, point3D &intersection, point3D &normal){

    point3D distance = center_ - start;
    double mag = distance.dot_product(direction);
    double distFromCenter = distance.dot_product(distance) - mag*mag;

    double t = sqrt(radius_*radius_ - distFromCenter);

    point3D dir2 = direction;
    point3D start2 = start;
    double t0 = mag-t;
    intersection = start2 + (dir2)*t0;
    normal = (intersection - center_).norm();
    bool intersects = !(mag < 0 || distFromCenter > radius_*radius_);

    return intersects;
}

