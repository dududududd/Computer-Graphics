#include "pch.h"
#include "OpenCylinder1.h"

#include"World.h"
const double OpenCylinder1::kEpsilon = 0.001;

OpenCylinder1::OpenCylinder1(void)
	:GeometricObject(),y0(-1.0),y1(1.0),
	radius(1.0),inv_radius(1.0),bbox()
{

}

OpenCylinder1::OpenCylinder1(const double _y0, const double _y1, const double _radius)
	:GeometricObject(),y0(_y0),y1(_y1),radius(_radius),bbox()
{
	inv_radius = 1.0 / radius;
}

OpenCylinder1::~OpenCylinder1(void)
{

}

bool OpenCylinder1::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0*(ox*dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4 * a*c;

	if (disc < 0.0)
		return(false);
	else
	{
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b - e) / denom;//小根

		if (t > kEpsilon)
		{
			double yhit = oy + t * dy;
			if (yhit > y0&&yhit < y1)
			{
				tmin = t;
				sr.normal = Normal((ox + t * dx)*inv_radius, 0.0, (oz + t * dz)*inv_radius);

				//内击测试

				/*if (-ray.d*sr.normal < 0.0)
				{
					sr.normal = -sr.normal;
				}*/
				sr.local_hit_point = ray.o + tmin * ray.d;

				return(true);
			}
		}
		t = (-b + e) / denom;//大根
		
		if (t > kEpsilon)
		{
			double yhit = oy + t * dy;

			if (yhit > y0&&yhit < y1)
			{
				tmin = t;
				sr.normal = Normal((ox + t * dx)*inv_radius, 0.0, (oz + t * dz)*inv_radius);

				//为了在透明对象着色中不给内表面着色造成错误，不使用法线逆置
				//撞击内表面试验
				/*if (-ray.d*sr.normal < 0.0)
				{
					sr.normal = -sr.normal;
				}*/
				sr.local_hit_point = ray.o + tmin * ray.d;

				return(true);
			}
		}

		return(false);
	}
}

bool OpenCylinder1::shadow_hit(const Ray & ray, float & tmin) const
{
	double t;
	Normal normal;//碰撞点的临时法矢量
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0*(ox*dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a*c;

	if (disc < 0.0)
		return(false);
	else
	{
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b - e) / denom;//小根

		if (t > kEpsilon)
		{
			double yhit = oy + t * dy;
			if (yhit > y0&&yhit < y1)
			{
				tmin = t;

				return(true);
			}
		}
		t = (-b + e) / denom;//大根

		if (t > kEpsilon)
		{
			double yhit = oy + t * dy;

			if (yhit > y0&&yhit < y1)
			{
				tmin = t;

				return(true);
			}
		}

		return(false);
	}
}

BBox OpenCylinder1::get_bounding_box(void)
{
	double delta = 0.0001;
	bbox = BBox(-radius - delta, radius + delta, y0 - delta, y1 + delta, -radius - delta, radius + delta);
	return(this->bbox);
}

BBox OpenCylinder1::set_bounding_box(void)
{
	bbox = get_bounding_box();
	return(this->bbox);
}
