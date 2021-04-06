#pragma once
#include <iostream>
#include "Point3d.hpp"
#include "Point2d.hpp"
#include <vector>
#include "Ray.hpp"
#include "Mesh3d.hpp"
#include "Plane2d.hpp"
#include <future>

class Camera
{
private:
    //Position of the observer
    Point3d Position;
    //Orientation of the observer
    Point3d Normal;
    Point3d Oriz;
    Point3d Vert;

    bool Ortho = false;
    //vector of the streight lines prgected from the mesh
    std::vector<Ray *> rays;
    Plane2d *plane = NULL;
    std::vector<Point2d *> view;

public:
    Camera(){};
    Camera(Point3d);
    Camera(const Camera &);
    ~Camera();

    Point3d getPosition() const { return Position; };
    Point3d getNormal() const { return Normal; };
    Plane2d *getPlane() const { return plane; };
    Point3d getOriz() { return Oriz; };
    Point3d getVert() { return Vert; };
    Ray *getRay(int i) const;
    Point2d *getView(int i) const;
    int getnview() { return view.size(); };

    void pushView(Point2d * p);

    void Move(Point3d);
    void Rotate(Point3d);
    void Reset();
    void Orth(bool);
    void Compute_Plane();
    void Compute_Rays(const Mesh3d &);
    void Compute_View();

    void Parallel(const Mesh3d &);

};