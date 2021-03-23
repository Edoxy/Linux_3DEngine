#include <math.h>
#include "headers/Camera.hpp"

Camera::Camera(Point3d p)
{
    position = p;
    normal = Point3d(1, 0, 0);
    focal = 50;
}

Camera::Camera(const Camera& cam)
{
    position = cam.position;
    normal = cam.normal;
    focal = cam.focal;
}

void Camera::move_to(Point3d p)
{
    position = p;
}

void Camera::rotate(Point3d& p)
{
    normal = *p.normalize();
}

void Camera::reset()
{
    position = Point3d(0, 0, 0);
    normal = Point3d(1, 0, 0);
    focal = 20;
}

void Camera::set_focal(float f)
{
    focal = f;
}

void Camera::orth(bool is)
{
    orthographic = is;
}