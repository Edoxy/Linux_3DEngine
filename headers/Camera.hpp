#pragma once
#include "Point3d.hpp"

class Camera
{
    private:
    Point3d position;
    Point3d normal;
    float focal;
    bool orthographic = false;

    public:
    Camera(){};
    Camera(Point3d);
    Camera(const Camera &);
    ~Camera();

    void move_to(Point3d);
    void rotate(Point3d &);
    void reset();
    void set_focal(float);
    void orth(bool);
};