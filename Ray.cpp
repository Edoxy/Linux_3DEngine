#include "headers/Ray.hpp"
#include "headers/Point3d.hpp"

Ray::Ray(Point3d t, Point3d p, bool is_point)
{
    if (is_point)
    {
        compute_points(t, p);
    }
    else
    {
        Tangent = t;
        Point = p;
    }
}

void Ray::compute_points(Point3d p1, Point3d p2)
{
    Tangent = *(p1 - p2).normalize();
    Point = p1;
}