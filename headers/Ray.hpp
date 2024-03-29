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
    Ray(const Ray&);

    void setTangent(Point3d t) { Tangent = t; };
    void setPoint(Point3d p) { Point = p; };

    Point3d getTangent() const {return Tangent; };
    Point3d getPoint() const {return Point; };

    void Compute_Points(Point3d, Point3d);
};
