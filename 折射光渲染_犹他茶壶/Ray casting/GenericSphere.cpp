#include "pch.h"
#include "GenericSphere.h"

#include"Constants.h"
#include"World.h"

GenericSphere::GenericSphere(void)
	:GeometricObject()
{
}

GenericSphere::~GenericSphere(void)
{
}

bool GenericSphere::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double t;
	Vector3D temp = ray.o;
	double a = ray.d*ray.d;
	double b = 2.0*temp*ray.d;
	double c = temp * temp - 1;
	double disc = b * b - 4.0*a*c;

	if (disc <= 0.0)
		return(false);
	else
	{
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b - e) / denom;

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d);
			sr.local_hit_point = ray.o + t * ray.d;
			return(true);
		}

		t = (-b + e) / denom;

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d);
			sr.local_hit_point = ray.o + t * ray.d;
			return(true);
		}
	}
	return(false);
}

bool GenericSphere::shadow_hit(const Ray & ray, float & tmin) const
{
	double t;
	Vector3D temp = ray.o;
	double a = ray.d*ray.d;
	double b = 2.0*temp*ray.d;
	double c = temp * temp - 1;
	double disc = b * b - 4.0*a*c;

	if (disc <= 0.0)
		return(false);
	else
	{
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b - e) / denom;

		if (t > kEpsilon)
		{
			tmin = t;
			return(true);
		}

		t = (-b + e) / denom;

		if (t > kEpsilon)
		{
			tmin = t;
			return(true);
		}
	}
	return(false);
}