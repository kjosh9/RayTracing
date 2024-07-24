#ifndef PLANE_HPP
#define PLANE_HPP

#include "shadedObject.hpp"

class Plane: public ShadedObject{

public:
    Plane();
    Plane(double lambert,
          point3D location,
          Color color,
          point3D normal);
    Plane(const Plane& rhs);

    ~Plane();

    Plane& operator=(const Plane& rhs);

    point3D normal();

    bool intersects(point3D start,
                    point3D direction,
                    point3D &intersection,
                    point3D &normal);

private:
    point3D normal_;
};

#endif
