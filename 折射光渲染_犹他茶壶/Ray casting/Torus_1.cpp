#include "pch.h"
#include "Torus_1.h"

#include"World.h"
#include"Maths.h"

Torus_1::Torus_1(void)
	:GeometricObject(),
	center(0.0), radius1(1.0), radius2(2.0), normal(0.0, 0.0, 1.0)
{

}

Torus_1::Torus_1(const Point3D & _p, const double _r1, const double _r2, Normal & _normal)
	:GeometricObject(),
	center(_p), radius1(_r1), radius2(_r2), normal(_normal)
{

}

Torus_1::~Torus_1(void)
{
}

bool Torus_1::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	float t = (center - ray.o)*normal / (ray.d*normal);

	if (t <= kEpsilon)
		return(false);

	Point3D p = ray.o + t * ray.d;
	double r1_squared = pow(radius1, 2.0);
	double r2_squared = pow(radius2, 2.0);

	if (center.Distance_Square(p) > r1_squared&&center.Distance_Square(p) < r2_squared)
	{
		tmin = t;
		sr.normal = normal;
		/*if (sr.normal*-ray.d < 0.0)
			sr.normal = -sr.normal;*/
		sr.local_hit_point = p;

		return(true);
	}

	else
	{
		return(false);
	}
}

bool Torus_1::shadow_hit(const Ray & ray, float & tmin) const
{
	float t = (center - ray.o)*normal / (ray.d*normal);

	if (t <= kEpsilon)
		return(false);

	Point3D p = ray.o + t * ray.d;
	double r1_squared = pow(radius1, 2.0);
	double r2_squared = pow(radius2, 2.0);

	if (center.Distance_Square(p) > r1_squared&&center.Distance_Square(p) < r2_squared)
	{
		tmin = t;

		return(true);
	}

	else
	{
		return(false);
	}
}

BBox Torus_1::get_bounding_box(void)
{
	double delta = 0.0001;
	this->bbox = BBox(-radius2 - delta, radius2 + delta, -delta, delta, -radius2 - delta, radius2 + delta);
	return(this->bbox);
}

BBox Torus_1::set_bounding_box(void)
{
	this->bbox = get_bounding_box();
	return(this->bbox);
}