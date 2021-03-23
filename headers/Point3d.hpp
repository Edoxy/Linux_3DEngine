#pragma once

class Point3d
{
    private:
    double x;
    double y;
    double z;

    public:
    Point3d(){};
    Point3d(double, double, double);
    Point3d(const Point3d &);

    void Setx(double x1){x = x1;};
    void Sety(double y1){y = y1;};
    void Setz(double z1){z = z1;};

    const double Getx(){return x;};
    const double Gety(){return y;};
    const double Getz(){return z;};

    double norm();
    Point3d* normalize();
    
};