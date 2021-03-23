#include <vector>
#include <iostream>
#include "headers/Point3d.hpp"
#include "headers/Mesh3d.hpp"

using namespace std;

Mesh3d::Mesh3d(const Mesh3d &mesh)
{
    numberOfPoints = mesh.numberOfPoints;
    for (int i = 0; i < numberOfPoints; i++)
    {
        Point3d *p = new Point3d(*mesh.Points[i]);
        Points.push_back(p);
    }
}

void Mesh3d::addPoint(Point3d &point)
{
    numberOfPoints++;
    Points.push_back(&point);
}

const Point3d *Mesh3d::getPoint(int pos) const
{
    if (pos >= numberOfPoints)
    {
        cout << "ERROR!: Out of index point" << endl;
        //Return a reference to a temporary variable
        return new Point3d();
    }
    return Points[pos];
}