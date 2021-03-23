#include <iostream>
#include <math.h>
#include "headers/Camera.hpp"
#include "headers/Ray.hpp"

using namespace std;

Camera::Camera(Point3d p)
{
    position = p;
    normal = Point3d(1, 0, 0);
    angle = 50;
}

Camera::Camera(const Camera &cam)
{
    position = cam.position;
    normal = cam.normal;
    angle = cam.angle;
}

void Camera::move_to(Point3d p)
{
    position = p;
}

void Camera::rotate(Point3d &p)
{
    normal = *p.normalize();
}

void Camera::reset()
{
    position = Point3d(0, 0, 0);
    normal = Point3d(1, 0, 0);
    angle = 20;
}

void Camera::set_angle(float f)
{
    angle = f;
}

void Camera::orth(bool is)
{
    ortho = is;
}

void Camera::compute_rays(const Mesh3d &mesh)
{
    const int n = mesh.Getn_points();
    if (!ortho)
    {
        for (int i = 0; i < n; i++)
        {
            Ray *temp_ray = new Ray(*mesh.getPoint(i), position);
            rays.push_back(temp_ray);
        }
    }
}

Ray *Camera::GetRay(int i) const
{
    if (i >= rays.size())
    {
        cout << "ERROR!: Out of index point" << endl;
        //Return a reference to a temporary variable
        return new Ray();
    }
    else
    {
        return rays[i];
    }
}