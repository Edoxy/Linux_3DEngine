#include "headers/Point2d.hpp"
#include <math.h>

Point2d::Point2d(float x1, float y1)
{
    x = x1;
    y = y1;
}

Point2d::Point2d(const Point2d & point)
{
    x = point.x;
    y = point.y;
}

double Point2d::norm(unsigned int n = 2)
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