#include "header.hpp"

using namespace std;

enum edirection { STOP = 0, LEFT, RIGHT, UP, DOWN, FORWARD, BACKWARD};
edirection DIR = STOP;
bool CLOSE = false;

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
        Point3d *p = x->normalize();
        cout << ". : " << *p;
        cout << p->norm() << endl;
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
        Point3d *p = x->normalize();
        mesh->addPoint(p);
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

void Input()
{
    if (_kbhit())
	{
		char prova;
		cin >> prova;
		switch (prova)
		{
		case 'a':
			DIR = LEFT;
			break;
		case 'd':
			DIR = RIGHT;
			break;
		case 'w':
			DIR = UP;
			break;
		case 's':
			DIR = DOWN;
			break;
        case 'r':
            DIR = FORWARD;
            break;
        case 'f':
            DIR = BACKWARD;
            break;
		case 'x':
			CLOSE = true;
			break;
		}
	}
}
int Display::n = 0;
int Mesh3d::n = 0;
int Ray::n = 0;
int Point3d::n = 0;
int Point2d::n = 0;
int Plane2d::n = 0;
int Camera::n = 0;

int main()
{
    fputs("\e[?25l", stdout);
    //cout << test();
    Mesh3d mesh;
    //creating a CUBE
    const double k = 1;
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
    /*for (float i = 0; i <= k; i++)
    {
        mesh.addPoint(new Point3d(-1 + i / k, -1 + i / k, -1));
        mesh.addPoint(new Point3d(-1 + i / k, 1 - i / k, -1 + i / k));
        mesh.addPoint(new Point3d(1 - i / k, 1 - i / k, -1 + i / k));
        mesh.addPoint(new Point3d(1 - i / k, -1 + i / k, -1 + i / k));
        mesh.addPoint(new Point3d(-1 + i / k, -1 + i / k, -1 + i / k));


        mesh.addPoint(new Point3d(-1 + i / k, 1 - i / k, 1 - i / k));
        mesh.addPoint(new Point3d(1 - i / k, 1 - i / k, 1 - i / k));
        mesh.addPoint(new Point3d(1 - i / k, -1 + i / k, 1 - i / k));
        mesh.addPoint(new Point3d(-1 + i / k, -1 + i / k, 1 - i / k));
    }*/

    //setting the camera
    float radius = 4;
    const double ALPHA = 0.1;
    Camera cam(Point3d(0, radius, 0));

    Display display;

    //render loop
    int i = 0;
    while (!CLOSE)
    {
        cout << Point3d::n << " " << Ray::n << endl;
        printf("\e[2j\e[H");
        display.Clear();

        Point3d pos(0, 0, 0);
        Point3d Right = cam.getVert();
        Point3d Normal = cam.getNormal();
        Normal = Normal.scalar(ALPHA);
        Right = Right.scalar(ALPHA);
        Input();
        switch (DIR)
        {
            case LEFT:
                Right = Right.scalar(-1);
                pos = Right;
                break;
            case RIGHT:
                pos = Right;
                break;
            case UP:
                pos.Setz(ALPHA);
                break;
            case DOWN:
                pos.Setz(-ALPHA);
                break;
            case FORWARD:
                pos = Normal;
                break;
            case BACKWARD:
                Normal = Normal.scalar(-1);
                pos = Normal;
                break;
            default:
                break;
        }
        Point3d tmp_pos = cam.getPosition();
        Point3d newpos = pos + tmp_pos;

        cam.move_to(newpos);
        Ray tmp;
        tmp.compute_points(cam.getPosition(), Point3d(0, 0, 0));
        Point3d dir = tmp.getTangent();
        
        cout << "INIT:   " << Point3d::n << " " << Ray::n << " " << Plane2d::n <<endl;
        cam.rotate(dir);
        cout << "ROTATE: " << Point3d::n << " " << Ray::n << " " << Plane2d::n <<endl;
        cam.compute_rays(mesh);
        cout << "RAYS:   " << Point3d::n << " " << Ray::n << " " << Plane2d::n <<endl;
        cam.compute_plane();
        cout << "PLANE:  " << Point3d::n << " " << Ray::n << " " << Plane2d::n <<endl;
        cam.compute_view();
        cout << "VIEW:   " << Point3d::n << " " << Ray::n << " " << Plane2d::n <<endl;
        cout << cam.getNrays() << " " << cam.getNview() << endl;
        display.Draw(cam);
        cam.reset();
        cout << "RESET:  " << Point3d::n << " " << Ray::n << " " << Plane2d::n <<endl;
        DIR = STOP;
        i++;
        cout << i << endl;
        cout << cam.getNrays() << " " << cam.getNview() << endl;
        cout << "END:    " << Point3d::n << " " << Ray::n << " " << Plane2d::n <<endl;
    }
}
