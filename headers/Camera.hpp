#pragma once
#include "Point3d.hpp"
#include "Point2d.hpp"
#include <vector>
#include "Ray.hpp"
#include "Mesh3d.hpp"
#include "Plane2d.hpp"

class Camera
{
private:
    //Position of the observer
    Point3d Position;
    //Orientation of the observer
    Point3d Normal;
    Point3d Oriz;
    Point3d Vert;
    //info about the kid of view to produce
    float Angle;
    bool Ortho = false;
    //vector of the streight lines prgected from the mesh
    std::vector<Ray *> rays;
    Plane2d *plane;
    std::vector<Point2d*> view;

public:
    Camera(){};
    Camera(Point3d);
    Camera(const Camera &);
    ~Camera();

    Point3d getPosition() const{ return Position;};
    Point3d getNormal() const { return Normal;};
    Point3d getOriz() const { return Oriz;};
    Point3d getVert() const { return Vert;};

    void move_to(Point3d);
    void rotate(Point3d);
    void reset();
    void set_angle(float);
    void orth(bool);
    void compute_rays(const Mesh3d &);
    void compute_plane();
    void compute_view();

    Ray *getRay(int i) const;
    Point2d *getView(int i) const;
    int getnview(){return view.size();};
};