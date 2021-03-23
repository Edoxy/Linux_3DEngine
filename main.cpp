#include <iostream>
#include <vector>
#include <string>
#include "headers/Point2d.hpp"
#include "headers/Point3d.hpp"
#include "headers/Camera.hpp"
#include "headers/Display.hpp"

using namespace std;

bool test()
{
    //test the 3D points class and creation
    cout << "TEST RUNNING..." << endl;
    vector<Point3d *> rnd_mesh;
    
    const unsigned int UNITS = 10;

    cout << "COORDINATES:" << endl;
    for (int i = 0; i < UNITS; i++)
    {
        //creation of random 3d points
        float x = rand()/3.0;
        float y = rand()/3.0;
        float z = rand()/3.0;

        cout << x << " " << y << " " << z << endl;

        rnd_mesh.push_back(new Point3d(x, y, z));
    }
    //print the coordinates
    cout << "THIS ARE THE POINTS THAT WERE CREATED:" << endl;
    for (Point3d* p : rnd_mesh)
    {
        cout << ". : " << p -> Getx() << " " << p->Gety() << " " << p->Getz() << endl;
        cout << p->norm() << endl;
    }
    cout << "NORMALIZE TEST:" << endl;
    for (Point3d* x : rnd_mesh)
    {
        Point3d* p = x->normalize();
        cout << ". : " << p -> Getx() << " " << p->Gety() << " " << p->Getz() << endl;
        cout << p->norm() << endl;
    }

    cout << "TEST FINISHED" << endl;
    return true;
}

int main()
{

    Point2d *point = new Point2d(1, 4);
    cout << point->Getx() << " " << point->Gety() << endl;

    cout << test();
    
}