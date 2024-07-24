#include "point3d.hpp"
#include <stdlib.h>
#include <cmath>

point3D::point3D():
    x_{0},
    y_{0},
    z_{0}
{
}

point3D::point3D(double x, double y, double z):
    x_{x},
    y_{y},
    z_{z}
{
}

point3D::point3D(const point3D& rhs){
    x_ = rhs.x_;
    y_ = rhs.y_;
    z_ = rhs.z_;
}

point3D::~point3D() {

}

bool point3D::operator==(const point3D& rhs) const {
    return rhs.x_ == x_ &&
            rhs.y_ == y_ &&
            rhs.z_ == z_;
}

point3D& point3D::operator=(const point3D& rhs) {
    if(this == &rhs){
        return *this;
    }

    x_ = rhs.x_;
    y_ = rhs.y_;
    z_ = rhs.z_;
    return *this;
}

double point3D::x() {
    return x_;
}

double point3D::y() {
    return y_;
}

double point3D::z() {
    return z_;
}

void point3D::set_x(double x)
{
    x_ = x;
}

void point3D::set_y(double y)
{
    y_ = y;
}

void point3D::set_z(double z)
{
    z_ = z;
}

point3D point3D::operator-(const point3D &rhs) {
    return point3D(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
}

point3D point3D::operator+(const point3D &rhs) {
    return point3D(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
}

point3D point3D::operator*(const point3D &rhs) {
    return point3D(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_);
}

double point3D::dot_product(const point3D &rhs) {
    return x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_;
}

point3D point3D::norm() {
    double mag = sqrt(x_*x_ + y_*y_ + z_*z_);
    return point3D(x_/mag, y_/mag, z_/mag);
}

point3D point3D::operator *(double scalar) {
    return point3D(x_*scalar, y_*scalar, z_*scalar);
}
