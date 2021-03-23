#include "headers/Points2d.hpp"
#include <math.h>

Points2d::Points2d(float x1, float y1)
{
    x = x1;
    y = y1;
}

Points2d::Points2d(const Points2d & point)
{
    x = point.x;
    y = point.y;
}

double Points2d::norm(unsigned int n = 2)
{
    float norm;
    if (n = 2)
    {
        norm = sqrt(x*x + y*y);
    }else
    {
        norm = x + y;
    }

    return norm;
}