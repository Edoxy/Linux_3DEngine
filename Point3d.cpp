#include "headers/Point3d.hpp"
#include <math.h>
#include <iostream>

Point3d::Point3d(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;

    n++;
    //std::cout << "point created" << std::endl;
}

Point3d::Point3d(const Point3d &point)
{
    x = point.x;
    y = point.y;
    z = point.z;

    n++;
    //std::cout << "point copied" << std::endl;
}

Point3d::~Point3d()
{
    n--;
    //std::cout << "point destroid" << std::endl;
}

double Point3d::norm()
{
    return sqrt(x * x + y * y + z * z);
}

Point3d *Point3d::normalize()
{
    const double norm = this->norm();
    return new Point3d(this->x / norm, this->y / norm, this->z / norm);
}

Point3d Point3d::operator+(const Point3d &point) const 
{
    return Point3d(x + point.x, y + point.y, z + point.z);
}

Point3d Point3d::operator-(const Point3d &point) const 
{
    return Point3d(x - point.x, y - point.y, z - point.z);
}

double Point3d::operator*(Point3d &point)
{
    return x * point.x + y * point.y + z * point.z;
}

std::ostream &operator<<(std::ostream &os, const Point3d &p)
{
    os << p.x << " | " << p.y << " | " << p.z << std::endl;
    return os;
}

Point3d Point3d::x_vett(Point3d &point)
{
    double x1 = (y * point.Getz()) - ((z * point.Gety()));
    double y1 = (z * point.Getx()) - (x * point.Getz());
    double z1 = (x * point.Gety()) - (y * point.Getx());
    return Point3d(x1, y1, z1);
}

Point3d Point3d::scalar(double a)
{
    double x1 = x * a;
    double y1 = y * a;
    double z1 = z * a;
    return Point3d(x1, y1, z1);
}