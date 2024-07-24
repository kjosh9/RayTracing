#ifndef SHADEDOBJECT_HPP
#define SHADEDOBJECT_HPP

#include "point3d.hpp"
#include "color.hpp"

class ShadedObject{

public:
    ShadedObject();

    ShadedObject(double lambert, point3D location, Color color);

    ShadedObject(const ShadedObject& rhs);

    ~ShadedObject();

    ShadedObject& operator=(const ShadedObject& rhs);

    double lambert();

    point3D center();

    Color color();

    virtual bool intersects(const point3D start, const point3D direction, point3D &intersction, point3D &normal) =0;

protected:
    double lambert_;
    point3D center_;
    Color color_;
};

#endif
