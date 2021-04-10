#include "pch.h"
#include "RGBColor.h"

RGBColor::RGBColor(void)
	:r(0.0), g(0.0), b(0.0)
{

}

RGBColor::RGBColor(const double a)
	: r(a), g(a), b(a)
{

}

RGBColor::RGBColor(const double _r, const double _g, const double _b)
	: r(_r), g(_g), b(_b)
{

}

RGBColor::RGBColor(const RGBColor& rhs)
	: r(rhs.r), g(rhs.g), b(rhs.b)
{

}

RGBColor::~RGBColor(void)
{

}

RGBColor RGBColor::operator+(const RGBColor& c)const
{
	return(RGBColor(this->r + c.r, this->g + c.g, this->b + c.b));
}

RGBColor operator*(const double a, const RGBColor& c)
{
	return(RGBColor(a*c.r, a*c.g, a*c.b));
}

//RGBColor RGBColor::operator*(const double a)const
//{
//	return(RGBColor(a*this->r, a*this->g, a*this->b));
//}

RGBColor RGBColor::operator/(const double a)const
{
	return(RGBColor(this->r / a, this->g / a, this->b / a));
}

RGBColor& RGBColor::operator/=(const double a)
{
	//从光照发现的L中的g值和b值是-nan(ind)，所以重新查找发现这里有错误
	this->r /= a;
	this->g /= a;
	this->b /= a;
	return(*this);
}

RGBColor& RGBColor::operator=(const RGBColor& c)
{
	if (this == &c)
		return(*this);
	else
	{
		this->r = c.r;
		this->g = c.g;
		this->b = c.b;
		return(*this);
	}
}

RGBColor RGBColor::operator*(const RGBColor& c)
{
	return RGBColor(this->r*c.r, this->g*c.g, this->b*c.b);
}

RGBColor& RGBColor::operator*=(const float a)
{
	this->r *= a;
	this->g *= a;
	this->b *= a;
	return(*this);
}

RGBColor RGBColor::powc(float p)const
{
	return(RGBColor(pow(this->r, p), pow(this->g, p), pow(this->b, p)));
}

RGBColor& RGBColor::operator+=(const RGBColor& c)
{
	this->r += c.r;
	this->g += c.g;
	this->b += c.b;
	return(*this);
}