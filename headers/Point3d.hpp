#pragma once
#include <iostream>
#include <string>

class Point3d
{
private:
    double x;
    double y;
    double z;

public:
    Point3d(){};
    Point3d(double, double, double);
    Point3d(const Point3d &);

    void Setx(double x1) { x = x1; };
    void Sety(double y1) { y = y1; };
    void Setz(double z1) { z = z1; };

    const double Getx() const { return x; };
    const double Gety() const { return y; };
    const double Getz() const { return z; };

    double norm();
    Point3d *normalize();

    Point3d operator+(Point3d &);
    Point3d operator-(Point3d &);
    double operator*(Point3d &);

    friend std::ostream &operator<<(std::ostream &, const Point3d &);

    Point3d x_vett(Point3d &);
};