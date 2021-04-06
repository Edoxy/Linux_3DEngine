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
}

Camera::Camera(const Camera &cam)
{
    Position = cam.Position;
    Normal = cam.Normal;
}

Camera::~Camera()
{
    Reset();
    delete plane;
}

void Camera::Move(Point3d p)
{
    Position = p;
}

void Camera::Rotate(Point3d p)
{
    Normal = p.Normalize();
}

void Camera::Reset()
{
    for (Ray *ray : rays)
    {
        delete ray;
    }
    for (Point2d *p : view)
    {
        delete p;
    }
    rays.clear();
    view.clear();
}

void Camera::Orth(bool is)
{
    Ortho = is;
}

void Camera::Compute_Rays(const Mesh3d &mesh)
{
    const int n = mesh.Getn_points();
    if (!Ortho)
    {
        for (int i = 0; i < n; i++)
        {
            Point3d t = *mesh.getPoint(i);
            Ray *tmp_ray = new Ray();
            tmp_ray->Compute_Points(t, Position);
            rays.push_back(tmp_ray);
        }
    }
}

void Camera::Compute_Plane()
{
    delete plane;
    Point3d P_plane = Position + Normal;
    plane = new Plane2d(Normal, P_plane);

    Vert = Point3d(1, -(Normal.getX() / Normal.getY()), 0).Normalize();
    Oriz = Vert.Vectorial_Product(Normal).Normalize();
    if (Oriz.getZ() < 0)
    {
        Vert = Point3d(-1, (Normal.getX() / Normal.getY()), 0).Normalize();
        Oriz = Vert.Vectorial_Product(Normal).Normalize();
    }
}

void Camera::Compute_View()
{
    for (Ray *ray : rays)
    {
        Point3d *d = plane->compute_intersection(*ray);

        Point3d c = plane->getPoint();
        Point3d p = (*d) - c;
        delete d;

        double nx = (p)*Oriz;
        double ny = (p)*Vert;
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

Point2d *Camera::getView(int i) const
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

void Camera::pushView(Point2d * point)
{
    if (point != NULL)
    {
        view.push_back(point);
    }
    return;
}



static std::mutex view_mutex;

static void Process(Point3d point, Camera *camera)
{
    Point3d Position = camera->getPosition();
    Point3d Oriz = camera->getOriz();
    Point3d Normal = camera->getNormal();
    Point3d Vert = camera->getVert();
    Plane2d * plane = camera->getPlane();

    Ray ray(point, Position, true);
    Point3d * intersection = plane->compute_intersection(ray);
    Point3d plane_pos = plane->getPoint();
    Point3d translated = (*intersection) - plane_pos;
    delete intersection;

    double nx = translated * Oriz;
    double ny = translated * Vert;

    if (abs(nx) < 0.5 && abs(ny) < 0.5)
    {
        nx = nx + 0.5;
        ny = ny + 0.5;

        std::lock_guard<std::mutex> lock(view_mutex);
        camera->pushView(new Point2d(nx, ny));
    }
}

//std::vector<std::future<void>> v_futures;

void Camera::Parallel(const Mesh3d& mesh)
{
    for (int i = 0; i < mesh.Getn_points(); i++)
    {
        Point3d point = *mesh.getPoint(i);
        async(launch::async, Process, point, this);
    }
}

