#include "pch.h"
#include "Point2D.h"

Point2D::Point2D(void)
	:x(0.0), y(0.0)
{

}

Point2D::Point2D(const double arg)
	: x(arg), y(arg)
{

}

Point2D::Point2D(const double _x, const double _y)
	: x(_x), y(_y)
{

}

Point2D::Point2D(const Point2D& p)
	: x(p.x), y(p.y)
{

}

Point2D::~Point2D(void)
{

}

Point2D& Point2D::operator=(const Point2D& rhs)
{
	if (this == &rhs)
		return(*this);
	else
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return (*this);
	}
}

Point2D Point2D::operator*(const double a)
{
	return(Point2D(x*a, y*a));
}