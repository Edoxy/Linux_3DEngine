#include "headers/Point3d.hpp"
#include <math.h>
#include <iostream>

Point3d::Point3d(const Point3d& point)
{
	x = point.x;
	y = point.y;
	z = point.z;
}

double Point3d::Norm() const
{
	double value;
	value = sqrt(x * x + y * y + z * z);
	return value;
}

Point3d Point3d::Normalize() const
{
	const double norm = Norm();
	return Point3d(x / norm, y / norm, z / norm);
}

Point3d Point3d::Vectorial_Product(const Point3d& point) const
{
	double new_x = (y * point.getZ()) - (z * point.getY());
	double new_y = (z * point.getX()) - (x * point.getZ());
	double new_z = (x * point.getY()) - (y * point.getX());
	return Point3d(new_x, new_y, new_z);
}

Point3d Point3d::operator+(const Point3d& point) const
{
	return Point3d(x + point.getX(), y + point.getY(), z + point.getZ());
}

Point3d Point3d::operator-(const Point3d& point) const
{
	return Point3d(x - point.getX(), y - point.getY(), z - point.getZ());
}

double Point3d::operator*(const Point3d& point) const
{
	double value = x * point.getX() + y * point.getY() + z * point.getZ();
	return value;
}

std::ostream& operator<<(std::ostream& os, const Point3d& point)
{
	os << point.getX() << " | " << point.getY() << " | " << point.getZ() << std::endl;
	return os;
}