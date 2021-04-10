#include "pch.h"
#include "Normal.h"
#include"Point3D.h"

Normal::Normal(void)
	:x(0.0), y(0.0), z(0.0)
{

}

Normal::Normal(const Normal& rhs)
	: x(rhs.x), y(rhs.y), z(rhs.z)
{

}

Normal::Normal(const Vector3D& rhs)
	:x(rhs.x),y(rhs.y),z(rhs.z)
{

}

Normal::Normal(const double _x, const double _y, const double _z)
	: x(_x), y(_y), z(_z)
{

}

Normal::~Normal(void)
{

}

Normal Normal::operator-(void)const
{
	return(Normal(-this->x, -this->y, -this->z));
}

Normal Normal::operator+(const Normal& m)const
{
	return(Normal(this->x + m.x, this->y + m.y, this->z + m.z));
}

double Normal::operator*(const Vector3D& u)const
{
	return(this->x*u.x + this->y*u.y + this->z*u.z);
}

double operator*(const Vector3D& u, const Normal& n)
{
	return(n.x*u.x + n.y*u.y + n.z*u.z);
}

Normal Normal::operator*(const double a)const
{
	return(Normal(a*this->x, a*this->y, a*this->z));
}

Normal operator*(const double a,const Normal& n)
{
	return(Normal(a*n.x, a*n.y, a*n.z));
}

Vector3D Normal::operator+(const Vector3D& u)const
{
	return(Vector3D(this->x + u.x, this->y + u.y, this->z + u.z));
}

Vector3D operator+(const Vector3D& u, const Normal& n)
{
	return(Vector3D(n.x + u.x, n.y + u.y, n.z + u.z));
}

Normal& Normal::operator=(const Normal& m)
{
	if (this == &m)
		return(*this);
	else
	{
		this->x = m.x;
		this->y = m.y;
		this->z = m.z;
		return(*this);
	}
}

Normal& Normal::operator=(const Vector3D& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return(*this);
}

Normal& Normal::operator=(const Point3D& p)
{
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
	return(*this);
}

Normal& Normal::operator+=(const Normal& m)
{
	this->x += m.x;
	this->y += m.y;
	this->z += m.z;
	return(*this);
}

void Normal::Normalize(void)
{
	double length = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	this->x /= length;
	this->y /= length;
	this->z /= length;
}

Normal operator*(const Matrix& mat, const Normal& n)
{
	return(Normal(mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
		mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
		mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z
	));
}