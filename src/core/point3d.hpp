#ifndef POINT3D_H
#define POINT3D_H


class point3D {

public:
    point3D();
    point3D(double x, double y, double z);
    point3D(const point3D& rhs);
    ~point3D();

    bool operator==(const point3D& rhs) const;
    point3D& operator=(const point3D& rhs);

    double x();
    double y();
    double z();

    void set_x(double);
    void set_y(double);
    void set_z(double);

    point3D operator-(const point3D &rhs);
    point3D operator+(const point3D &rhs);
    point3D operator*(const point3D &rhs);
    double dot_product(const point3D &rhs);
    point3D norm();
    point3D operator*(double scalar);

private:
    double x_;
    double y_;
    double z_;
};

#endif // POINT3D_H
