#include "header.hpp"

using namespace std;

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
        cout << p->Norm() << endl;
    }
    cout << "NORMALIZE TEST:" << endl;
    for (Point3d *x : rnd_mesh)
    {
        Point3d p = x->Normalize();
        cout << ". : " << p;
        cout << p.Norm() << endl;
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
    cout << e1.Vectorial_Product(e2);
    cout << e2.Vectorial_Product(e3);
    cout << e3.Vectorial_Product(e1);
    cout << e2.Vectorial_Product(e1);

    ///TESTING MESH 3D
    cout << "TESTING 3D MESH" << endl;

    Mesh3d *mesh = new Mesh3d();
    for (Point3d *x : rnd_mesh)
    {
        Point3d p = x->Normalize();
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

    Point3d *p = pi->compute_intersection(*ray);
    cout << "INTERSECTION : " << *p;

    //TESTING CAMERA
    cout << "TESTING CAMERA" << endl;
    Camera cam(Point3d(0, 3, 0));
    cam.Rotate(Point3d(0, -2, 0));
    cout << cam.getPosition() << cam.getNormal();
    cam.Compute_Rays(*mesh);
    cam.Compute_Plane();
    cam.Compute_View();

    Display display;
    display.Clear();
    display.Draw(cam);
    cout << "TEST FINISHED" << endl;
    return true;
}