#include <iostream>
#include <math.h>
#include "headers/Camera.hpp"
#include "headers/Ray.hpp"

using namespace std;

Camera::Camera(Point3d p)
{
    Position = p;
    Normal = Point3d(1, 0, 0);
    Angle = 50;
    n++;
}

Camera::Camera(const Camera &cam)
{
    Position = cam.Position;
    Normal = cam.Normal;
    Angle = cam.Angle;
    n++;
}

Camera::~Camera()
{
    reset();
}

void Camera::move_to(Point3d p)
{
    Position = p;
}

void Camera::rotate(Point3d p)
{
    Normal = *p.normalize();
}

void Camera::reset()
{
    for (Ray* ray : rays)
    {
        delete ray;
    }
    for (Point2d * p : view)
    {
        delete p;
    }
    rays.clear();
    view.clear();
    delete plane;
}

void Camera::set_angle(float f)
{
    Angle = f;
}

void Camera::orth(bool is)
{
    Ortho = is;
}

void Camera::compute_rays(const Mesh3d &mesh)
{
    const int n = mesh.Getn_points();
    if (!Ortho)
    {
        for (int i = 0; i < n; i++)
        {
            Ray *tmp_ray = new Ray();
            tmp_ray->compute_points(*mesh.getPoint(i), Position);
            rays.push_back(tmp_ray);
        }
    }
}

void Camera::compute_plane()
{
    Point3d P_plane = Position + Normal;
    plane = new Plane2d(Normal, P_plane);

    Vert = *Point3d(1, -(Normal.Getx() / Normal.Gety()),0).normalize();
    Oriz = *Vert.x_vett(Normal).normalize();
    if ( Oriz.Getz() < 0)
    {
        Vert =  *Point3d(-1, (Normal.Getx() / Normal.Gety()),0).normalize();
        Oriz = *Vert.x_vett(Normal).normalize();
    }
}

void Camera::compute_view()
{
    for (Ray* ray : rays)
    {
        Point3d * tmp = plane->compute_intersection(ray);
        Point3d tan = ray->getTangent();
        if(tmp == NULL || tan * Normal > 0)
        {
            //cout << "ERROR!: NO INTERSECTION" << endl;
        }else{
            Point3d p = *tmp;
            //cout << p;
            Point3d c = plane->getPoint();
            p = p - c;
            double nx = p * Oriz;
            double ny = p * Vert;
            //check if the point is in the field of view
            if (abs(nx) < 0.5 && abs(ny) < 0.5)
            {
                nx = nx + 0.5;
                ny = ny + 0.5;

                view.push_back(new Point2d(nx, ny));
            }
        }
        delete tmp;
    }
}

Ray *Camera::getRay(int i) const
{
    if (i >= rays.size())
    {
        cout << "ERROR!: Out of index point" << endl;
        //Return a reference to a NULL pointer
        return NULL;
    }
    else
    {
        return rays[i];
    }
}

Point2d* Camera::getView(int i) const
{
    if (i >= view.size())
    {
        cout << "ERROR!: Out of index point" << endl;
        //Return a reference to a Null pointer
        return NULL;
    }
    else
    {
        return view[i];
    }
}
