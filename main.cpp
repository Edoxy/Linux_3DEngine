#include "header.hpp"
#include <chrono>
#include <unistd.h>
#include <memory>

using namespace std;

struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage()
{
    cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

bool test()
{
    //test the 3D points class and creation
    cout << "TEST RUNNING..." << endl;

    ///TESTING 3D POINTS
    cout << "TESTING 3D POINTS" << endl;
    vector<Point3d *> rnd_mesh;

    const unsigned int UNITS = 20;

    cout << "COORDINATES:" << endl;
    for (int i = 0; i < UNITS; i++)
    {
        //creation of random 3d points
        float x = rand() / 3.0;
        float y = rand() / 3.0;
        float z = rand() / 3.0;

        cout << x << " " << y << " " << z << endl;

        rnd_mesh.push_back(new Point3d(x, y, z));
    }
    //print the coordinates
    cout << "THIS ARE THE POINTS THAT WERE CREATED:" << endl;
    for (Point3d *p : rnd_mesh)
    {
        cout << ". : " << *p;
        cout << p->norm() << endl;
    }
    cout << "NORMALIZE TEST:" << endl;
    for (Point3d *x : rnd_mesh)
    {
        Point3d p = x->normalize();
        cout << ". : " << p;
        cout << p.norm() << endl;
    }
    //TEST SCALAR PRODUCT
    cout << "TEST SCALAR PRODUCT" << endl;
    Point3d e1 = Point3d(1, 0, 0);
    Point3d e2 = Point3d(0, 1, 0);
    Point3d e3 = Point3d(0, 0, 1);
    cout << e1 * e1 << endl;
    cout << e1 * e2 << endl;
    cout << e2 * e3 << endl;
    cout << e3 * e1 << endl;
    //TEST SCALAR PRODUCT
    cout << "TEST VECTORIAL PRODUCT" << endl;
    cout << e1.x_vett(e2);
    cout << e2.x_vett(e3);
    cout << e3.x_vett(e1);
    cout << e2.x_vett(e1);

    ///TESTING MESH 3D
    cout << "TESTING 3D MESH" << endl;

    Mesh3d *mesh = new Mesh3d();
    for (Point3d *x : rnd_mesh)
    {
        Point3d p = x->normalize();
        mesh->addPoint(&p);
    }
    for (int i = 0; i < mesh->Getn_points(); i++)
    {
        const Point3d *p = mesh->getPoint(i);
        cout << "MESH : " << *p;
    }

    cout << "TESTING PLANE..." << endl;
    Plane2d *pi = new Plane2d(Point3d(2, 0, 0), Point3d(0, 0, 0));
    cout << pi->getNormal() << pi->getPoint();

    cout << "TESTING RAY..." << endl;
    Ray *ray = new Ray(Point3d(-1, 0, 0), Point3d(1, 1, 0));
    cout << ray->getTangent() << ray->getPoint();

    cout << "TESTING INTERSECTION" << endl;

    Point3d *p = pi->compute_intersection(ray);
    cout << "INTERSECTION : " << *p;

    //TESTING CAMERA
    cout << "TESTING CAMERA" << endl;
    Camera cam(Point3d(0, 3, 0));
    cam.rotate(Point3d(0, -2, 0));
    cout << cam.getPosition() << cam.getNormal();
    cam.compute_rays(*mesh);
    cam.compute_plane();
    cam.compute_view();

    Display display;
    display.Clear();
    display.Draw(cam);
    cout << "TEST FINISHED" << endl;
    return true;
}

int main()
{
    fputs("\e[?25l", stdout);
    //cout << test();
    Mesh3d mesh;
    //creating a CUBE
    const double k = 1000;
    for (float i = 1; i <= 2 * k; i++)
    {
        mesh.addPoint(new Point3d(1 - i / k, 1, 1));
        mesh.addPoint(new Point3d(1, 1 - i / k, 1));
        mesh.addPoint(new Point3d(1, 1, 1 - i / k));
        mesh.addPoint(new Point3d(-1 + i / k, -1, -1));
        mesh.addPoint(new Point3d(-1, -1 + i / k, -1));
        mesh.addPoint(new Point3d(-1, -1, -1 + i / k));

        mesh.addPoint(new Point3d(-1 + i / k, 1, -1));
        mesh.addPoint(new Point3d(-1, 1, -1 + i / k));

        mesh.addPoint(new Point3d(1, -1, 1 - i / k));
        mesh.addPoint(new Point3d(1 - i / k, -1, 1));

        mesh.addPoint(new Point3d(1, 1 - i / k, -1));
        mesh.addPoint(new Point3d(-1, -1 + i / k, 1));
    }
    //adding a Piramid inside
    for (float i = 0; i <= k; i++)
    {
        mesh.addPoint(new Point3d(-1 + i / k, 1 - i / k, -1 + i / k));
        mesh.addPoint(new Point3d(1 - i / k, 1 - i / k, -1 + i / k));
        mesh.addPoint(new Point3d(1 - i / k, -1 + i / k, -1 + i / k));
        mesh.addPoint(new Point3d(-1 + i / k, -1 + i / k, -1 + i / k));

        mesh.addPoint(new Point3d(-1 + i / k, 1 - i / k, 1 - i / k));
        mesh.addPoint(new Point3d(1 - i / k, 1 - i / k, 1 - i / k));
        mesh.addPoint(new Point3d(1 - i / k, -1 + i / k, 1 - i / k));
        mesh.addPoint(new Point3d(-1 + i / k, -1 + i / k, 1 - i / k));
    }

    //setting the camera
    float radius = 4;

    Camera cam(Point3d(0, radius, 0));

    Display display;

    float t = 0;
    unsigned int micro_s = 14e3;
    //render loop
    while (t < 2 * 6.28)
    {
        printf("\e[2j\e[H");
        PrintMemoryUsage();
        auto start = chrono::high_resolution_clock::now();

        display.Clear();
        Point3d pos(-radius * sin(t), radius * cos(t), t - 6);
        Ray tmp;
        tmp.compute_points(pos, Point3d(0, 0, 0));
        Point3d dir = tmp.getTangent();

        cam.move_to(pos);

        cam.rotate(dir);

        cam.compute_rays(mesh);

        cam.compute_plane();

        cam.compute_view();

        display.Draw(cam);
        cam.reset();
 

        t += 0.03;
        usleep(micro_s);
        auto stop = chrono::high_resolution_clock::now();
        float duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();

        cout << "FPS =  " << 1000000 / duration << " " << duration << endl;

    }
}
