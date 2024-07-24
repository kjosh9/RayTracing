#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shadedObject.hpp"
#include <cmath>

class Sphere: public ShadedObject{

public:
    Sphere();

    Sphere(double lambert, point3D location, Color color, double radius);

    Sphere(const Sphere& rhs);

    ~Sphere();

    Sphere& operator=(const Sphere& rhs);

    double radius();

    bool intersects(const point3D start, const point3D direction, point3D &intersection, point3D &normal);

private:
    double radius_;
};

#endif
