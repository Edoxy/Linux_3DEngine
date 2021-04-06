#pragma once
#include <iostream>
#include <string>

class Point3d
{
private:
    double x;
    double y;
    double z;

public:
public:
	Point3d() {};
	Point3d(double x1 , double y1, double z1) : x(x1), y(y1), z(z1)
	{}
	Point3d(const Point3d&);

	double getX() const { return x; };
	double getY() const { return y; };
	double getZ() const { return z; };

	void setX(double x1) { x = x1; };
	void setY(double y1) { y = y1; };
	void setZ(double z1) { z = z1; };

	//calculate norm of the point
	double Norm() const;
	//Vector Normalized
	Point3d Normalize() const;
	Point3d Vectorial_Product(const Point3d&) const;

	Point3d operator+(const Point3d&) const;
	Point3d operator-(const Point3d&) const;
	double operator*(const Point3d&) const;

	friend std::ostream& operator<<(std::ostream&, const Point3d&);
};