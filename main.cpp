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

void *operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void *memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage()
{
    std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

int main()
{
    fputs("\e[?25l", stdout);
    //cout << test();
    Mesh3d mesh;
    //creating a CUBE
    const double k = 4000;
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
        //PrintMemoryUsage();
        auto start = chrono::high_resolution_clock::now();

        display.Clear();
        Point3d pos(-radius * sin(t), radius * cos(t), t - 6);
        Ray tmp(pos, Point3d(0, 0, 0), true);
        Point3d dir = tmp.getTangent();

        cam.Move(pos);

        cam.Rotate(dir);

        cam.Compute_Plane();
        //Don't know why but its faster not to use parallel method
        cam.Compute_Rays(mesh);
        cam.Compute_View();

        display.Draw(cam);

        cam.Reset();

        t += 0.03;
        //usleep(micro_s);
        auto stop = chrono::high_resolution_clock::now();
        float duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();

        cout << "FPS =  " << 1000000 / duration;
    }
}
