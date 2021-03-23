#pragma once
#include "Point3d.hpp"
#include <vector>
#include "Ray.hpp"
#include "Mesh3d.hpp"

class Camera
{
private:
    //Position of the observer
    Point3d position;
    //Orientation of the observer
    Point3d normal;
    //info about the kid of view to produce
    float angle;
    bool ortho = false;
    //vector of the streight lines prgected from the mesh
    std::vector<Ray *> rays;

public:
    Camera(){};
    Camera(Point3d);
    Camera(const Camera &);
    ~Camera();

    void move_to(Point3d);
    void rotate(Point3d &);
    void reset();
    void set_angle(float);
    void orth(bool);
    void compute_rays(const Mesh3d &);

    Ray *GetRay(int i) const;
};