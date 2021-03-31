#pragma once
#include "Point3d.hpp"
#include "Ray.hpp"

class Plane2d
{
private:
    Point3d Normal;
    Point3d Point;

public:
    static int n;

    Plane2d(){n ++;};
    Plane2d(Point3d, Point3d);
    Plane2d(const Plane2d &);
    ~Plane2d();

    Point3d getNormal() const { return Normal; };
    Point3d getPoint() const { return Point; };

    void setNormal(const Point3d &n) { Normal = n; };
    Point3d *compute_intersection(Ray *);
};