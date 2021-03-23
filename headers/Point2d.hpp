#pragma once

class Point2d
{
    private:
    float x;
    float y;

    public:
    Point2d();
    Point2d(float, float);
    Point2d(const Point2d &);
    ~Point2d();

    float Getx(){return x;};
    float Gety(){return y;};

    void Setx(float x1){x = x1;};
    void Sety(float y1){y = y1;};

    double norm(unsigned int);
};