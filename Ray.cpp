#include "headers/Ray.hpp"
#include "headers/Point3d.hpp"

Ray::Ray(Point3d t, Point3d p, bool is_point)
{
    if (is_point)
    {
        Compute_Points(t, p);
    }
    else
    {
        Tangent = t;
        Point = p;
    }
}

Ray::Ray(const Ray& ray)
{
    Tangent = ray.getTangent();
    Point = ray.getPoint();
}

void Ray::Compute_Points(Point3d p1, Point3d p2)
{
    Tangent = (p1 - p2).Normalize();
    Point = p1;
}