#include "pch.h"
#include "Point3D.h"

Point3D::Point3D(void)
	:x(0.0), y(0.0), z(0.0)
{

}

Point3D::Point3D(const Point3D& p)
	: x(p.x), y(p.y), z(p.z)
{

}

Point3D::Point3D(const double a)
	: x(a), y(a), z(a)
{

}

Point3D::Point3D(const double _x, const double _y, const double _z)
	: x(_x), y(_y), z(_z)
{

}

Point3D::~Point3D(void)
{

}

Point3D Point3D::operator+(const Vector3D& u)const
{
	return(Point3D(this->x + u.x, this->y + u.y, this->z + u.z));
}

Point3D Point3D::operator-(const Vector3D& u)const
{
	return(Point3D(this->x - u.x, this->y - u.y, this->z - u.z));
}

Vector3D Point3D::operator-(const Point3D& p)const
{
	return(Vector3D(this->x - p.x, this->y - p.y, this->z - p.z));
}

double Point3D::Distance_Square(const Point3D& p)const
{
	return(pow(this->x - p.x, 2) + pow(this->y - p.y, 2) + pow(this->z - p.z, 2));
}

double Point3D::Distance(const Point3D& p)const
{
	return(sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2) + pow(this->z - p.z, 2)));
}

float Point3D::distance(const Vector3D& v) const
{
	return(sqrt(pow(this->x - v.x, 2) + pow(this->y - v.y, 2) + pow(this->z - v.z, 2)));
}

Point3D& Point3D::operator=(const Point3D& rhs)
{
	if (this == &rhs)
		return(*this);
	else
	{
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		return(*this);
	}
}

Point3D Point3D::operator*(const double a)const
{
	return(Point3D(a*this->x, a*this->y, a*this->z));
}

Point3D operator*(const double a,const Point3D& p)
{
	return(Point3D(a*p.x, a*p.y, a*p.z));
}

Point3D operator*(const Matrix& mat, const Point3D& p)
{
	return(Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3]
		, mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3]
		, mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
}