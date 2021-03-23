#pragma once
#include <vector>
#include "Point3d.hpp"

class Mesh3d
{
    private:
    std::vector<Point3d *> Points;
    int numberOfPoints;

    public:
    Mesh3d(){numberOfPoints =0;};
    Mesh3d(const Mesh3d& );
    ~Mesh3d();

    int Getn_points() const {return numberOfPoints;};
    void addPoint(Point3d&);
    const Point3d* getPoint(int) const;
};