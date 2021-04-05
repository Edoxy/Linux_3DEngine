#include <iostream>
#include <math.h>
#include "headers/Camera.hpp"
#include "headers/Ray.hpp"
#include <future>

using namespace std;

Camera::Camera(Point3d p)
{
    Position = p;
    Normal = Point3d(1, 0, 0);
    Angle = 50;
}

Camera::Camera(const Camera &cam)
{
    Position = cam.Position;
    Normal = cam.Normal;
    Angle = cam.Angle;
}

Camera::~Camera()
{
    reset();
    delete plane;
}

void Camera::move_to(Point3d p)
{
    Position = p;
}

void Camera::rotate(Point3d p)
{
    Normal = p.normalize();
}

void Camera::reset()
{
    for (Ray *ray : rays)
    {
        delete ray;
    }
    for (Point2d * p : view)
    {
        delete p;
    }
    rays.clear();
    view.clear();

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
            Point3d t = *mesh.getPoint(i);
            Ray *tmp_ray = new Ray();
            tmp_ray->compute_points(t, Position);
            rays.push_back(tmp_ray);
        }
    }
}

void Camera::compute_plane()
{
    delete plane;
    Point3d P_plane = Position + Normal;
    plane = new Plane2d(Normal, P_plane);

    Vert = Point3d(1, -(Normal.Getx() / Normal.Gety()),0).normalize();
    Oriz = Vert.x_vett(Normal).normalize();
    if ( Oriz.Getz() < 0)
    {
        Vert = Point3d(-1, (Normal.Getx() / Normal.Gety()),0).normalize();
        Oriz = Vert.x_vett(Normal).normalize();
    }
}

void Camera::compute_view()
{
    for (Ray* ray : rays)
    {
        Point3d *d = plane->compute_intersection(*ray);

        Point3d c = plane->getPoint();
        Point3d p = (*d) - c;
        delete d;

        double nx = (p) * Oriz;
        double ny = (p) * Vert;
        //check if the point is in the field of view
        if (abs(nx) < 0.5 && abs(ny) < 0.5)
        {
            nx = nx + 0.5;
            ny = ny + 0.5;

            view.push_back(new Point2d(nx, ny));
        }
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

static std::mutex view_mutex;

void Camera::Parallel(const Mesh3d & mesh)
{
    for (int i = 0; i < mesh.Getn_points(); i++)
    {
        const Point3d point = *mesh.getPoint(i);
        async(launch::async, Process, point);
    }
}

static void Process(Point3d& p, Camera& c)
{
    Ray ray(p, c.getPosition(), true);
    Point3d *d = plane->compute_intersection(ray);
    
    Point3d c = plane->getPoint();
    Point3d s = (*d) - c;
    delete d;

    double nx = Oriz * s;
    double ny = s * Vert;
    //check if the point is in the field of view
    if (abs(nx) < 0.5 && abs(ny) < 0.5)
    {
        nx = nx + 0.5;
        ny = ny + 0.5;

        std::lock_guard<std::mutex> lock(view_mutex);
        view.push_back(new Point2d(nx, ny));
    } 
}