#pragma once
#include <math.h>
#include "Point3d.hpp"

class Ray
{
private:
    Point3d Tangent;
    Point3d Point;

public:
    Ray(){};
    Ray(Point3d, Point3d, bool = false);

    void setTangent(Point3d t) { Tangent = t; };
    void setPoint(Point3d p) { Point = p; };

    void compute_points(Point3d, Point3d);
};
