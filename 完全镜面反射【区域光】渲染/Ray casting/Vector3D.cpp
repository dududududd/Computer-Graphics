#include "pch.h"
#include "Vector3D.h"
#include"Point3D.h"
#include"Normal.h"

Vector3D::Vector3D(void)
	:x(0.0), y(0.0), z(0.0)
{

}

Vector3D::Vector3D(const Vector3D& rhs)
	: x(rhs.x), y(rhs.y), z(rhs.z)
{

}

Vector3D::Vector3D(const Point3D& p)
	: x(p.x),y(p.y), z(p.z)
{

}

Vector3D::Vector3D(const double a)
	: x(a), y(a), z(a)
{

}

Vector3D::Vector3D(const double _x, const double _y, const double _z)
	: x(_x), y(_y), z(_z)
{

}

Vector3D::~Vector3D(void)
{

}

Vector3D Vector3D::operator+(const Vector3D& v)const
{
	return(Vector3D(this->x + v.x, this->y + v.y, this->z + v.z));
}

Vector3D Vector3D::operator-(const Vector3D& v)const
{
	return(Vector3D(this->x - v.x, this->y - v.y, this->z - v.z));
}

float Vector3D::distance(const Point3D & p) const
{
	return(sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2) + pow(this->z - p.z, 2)));
}

Vector3D operator*(const double a, const Vector3D& v)
{
	return(Vector3D(a*v.x, a*v.y, a*v.z));
}

Vector3D Vector3D::operator*(const double a)const
{
	return(Vector3D(a*this->x, a*this->y, a*this->z));
}

Vector3D Vector3D::operator/(const double a)const
{
	return(Vector3D(this->x / a, this->y / a, this->z / a));
}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
	if (this == &v)
		return(*this);
	else
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return(*this);
	}
}

Vector3D & Vector3D::operator=(const Normal & n)
{
	this->x = n.x;
	this->y = n.y;
	this->z = n.z;
	return(*this);
}

double Vector3D::Length(void)
{
	return(sqrt(this->x*this->x + this->y*this->y + this->z*this->z));
}

double Vector3D::Length_Square(void)const
{
	return(this->x*this->x + this->y*this->y + this->z*this->z);
}

double Vector3D::operator*(const Vector3D& v)const
{
	return(this->x*v.x + this->y*v.y + this->z*v.z);
}

Vector3D Vector3D::operator^(const Vector3D& v)const
{
	return(Vector3D(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x));
}

Vector3D Vector3D::operator-(void)const
{
	return(Vector3D(-this->x, -this->y, -this->z));
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return(*this);
}

Vector3D& Vector3D::hat(void)
{
	double length = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	x /= length;
	y /= length;
	z /= length;
	return(*this);
}

void Vector3D::Normalize(void)
{
	double length = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	if (length == 0) return;
	this->x /= length; 
	this->y /= length;
	this->z /= length;
}

Vector3D operator*(const Matrix& mat, const Vector3D& v)
{
	return(Point3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z
		, mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z
		, mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}