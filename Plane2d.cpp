#include <iostream>
#include <math.h>
#include "headers/Plane2d.hpp"
#include "headers/Point3d.hpp"
#include "headers/Ray.hpp"

using namespace std;

Plane2d::Plane2d(const Plane2d& plane)
{

}

Point3d* Plane2d::compute_intersection(Ray* r)
{
    const float TOLL = 0.1;
    Ray ray = *r;
    Point3d u = ray.getTangent();
    if(abs(u * Normal) > TOLL)
    {
        Point3d P0 = ray.getPoint();
        Point3d w = P0 - Point;
        double S1 = -(Normal * w)/(Normal * u);

        double x = u.Getx() * S1 + P0.Getx();
        double y = u.Gety() * S1 + P0.Gety();
        double z = u.Getz() * S1 + P0.Getz();
        return new Point3d(x, y, z);
    }else
    {
        return NULL; //null pointer if there are no intersections or there is but very distant
    }

}