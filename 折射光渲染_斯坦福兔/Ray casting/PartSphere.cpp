#include "pch.h"
#include "PartSphere.h"

#include"Constants.h"

#include"World.h"

const double PartSphere::kEpsilon = 0.001;

PartSphere::PartSphere(void)
	:GeometricObject(),radius(1.0),center(0.0),
	phi_min(0.0),phi_max(TWO_PI),theta_min(0.0),
	theta_max(PI),cos_theta_min(1.0),cos_theta_max(-1.0)
{

}

PartSphere::PartSphere(const Point3D _center, const double _radius)
	:GeometricObject(),center(_center),radius(_radius),
	phi_min(0.0), phi_max(TWO_PI), theta_min(0.0),
	theta_max(PI), cos_theta_min(1.0), cos_theta_max(-1.0)
{
}

PartSphere::PartSphere(const Point3D _center, const double _radius, const double _phi_min, const double _phi_max, const double _theta_min, const double _theta_max)
	:GeometricObject(),center(_center),radius(_radius),phi_max(_phi_max*PI_ON_180),phi_min(_phi_min*PI_ON_180),theta_max(_theta_max*PI_ON_180),theta_min(_theta_min*PI_ON_180)
{
	this->cos_theta_min = cos(theta_min);
	this->cos_theta_max = cos(theta_max);
}

PartSphere::~PartSphere(void)
{

}

bool PartSphere::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d*ray.d;
	double b = 2.0*temp*ray.d;
	double c = temp * temp - radius * radius;
	double disc = b * b - 4.0*a*c;

	if (disc < 0.0)
		return(false);
	else
	{
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b - e) / denom;//小根

		if (t > kEpsilon)
		{
			Vector3D hit = ray.o + t * ray.d - center;

			float phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
			{
				phi += TWO_PI;
			}
			if (hit.y <= radius * cos_theta_min&&hit.y >= radius * cos_theta_max&&phi >= phi_min && phi <= phi_max)
			{
				tmin = t;
				sr.normal = (temp + t * ray.d) / radius;//向外指

				if (-ray.d*sr.normal < 0.0)//反向法线
				{						   //当光线击中里面
					sr.normal = -sr.normal;
				}
				sr.local_hit_point = ray.o + tmin * ray.d;
				return(true);
			}
		}
		t = (-b + e) / denom;//大根

		if (t > kEpsilon)
		{
			Vector3D hit = ray.o + t * ray.d - center;
			float phi = atan2(hit.x, hit.z);

			if (phi < 0.0)
			{
				phi += TWO_PI;
			}
			if (hit.y <= radius * cos_theta_min&&hit.y >= radius * cos_theta_max&&phi >= phi_min && phi <= phi_max)
			{
				tmin = t;
				sr.normal = (temp + t * ray.d) / radius;//向外指
				
				if (-ray.d*sr.normal < 0.0)//反向法线
				{						   //当光线击中里面
					sr.normal = -sr.normal;
				}
				sr.local_hit_point = ray.o + tmin * ray.d;
				return(true);
			}
		}
	}
	return(false);
}

bool PartSphere::shadow_hit(const Ray & ray, float & tmin) const
{
	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d*ray.d;
	double b = 2.0*temp*ray.d;
	double c = temp * temp - radius * radius;
	double disc = b * b - 4.0*a*c;

	if (disc < 0.0)
		return(false);
	else
	{
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b - e) / denom;//小根

		if (t > kEpsilon)
		{
			Vector3D hit = ray.o + t * ray.d - center;

			float phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
			{
				phi += TWO_PI;
			}
			if (hit.y <= radius * cos_theta_min&&hit.y >= radius * cos_theta_max&&phi >= phi_min && phi <= phi_max)
			{
				tmin = t;

				return(true);
			}
		}
		t = (-b + e) / denom;//大根

		if (t > kEpsilon)
		{
			Vector3D hit = ray.o + t * ray.d - center;
			float phi = atan2(hit.x, hit.z);

			if (phi < 0.0)
			{
				phi += TWO_PI;
			}
			if (hit.y <= radius * cos_theta_min&&hit.y >= radius * cos_theta_max&&phi >= phi_min && phi <= phi_max)
			{
				tmin = t;

				return(true);
			}
		}
		return(false);
	}
}
