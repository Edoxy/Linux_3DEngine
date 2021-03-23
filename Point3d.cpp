#include "headers/Point3d.hpp"
#include <math.h>

Point3d::Point3d(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;
}

Point3d::Point3d(const Point3d& point)
{
    x = point.x;
    y = point.y;
    z = point.z;
}

double Point3d::norm()
{
    return sqrt(x * x + y * y + z * z);
}

Point3d* Point3d::normalize()
{
    const double norm = this->norm();
    return new Point3d(this->x /norm, this->y /norm, this->z /norm);
}