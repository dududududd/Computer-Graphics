#include "pch.h"
#include "Sphere.h"

const double Sphere::kEpsilon = 0.001;
const double PI = 3.1415926535897932384;

Sphere::Sphere()
	:GeometricObject(), radius(1.0), center(0.0)
	, normal(0.0, 0.0, 1.0), sampler_ptr(nullptr),
	bbox(-radius, radius, -radius, radius, -radius, radius)
{
	inv_area = 1.0 / (4 * PI*pow(radius, 2));
}
	
Sphere::Sphere(const Point3D& _center, const double _radius)
	: GeometricObject(), radius(_radius), center(_center),
	sampler_ptr(nullptr),normal(0.0,0.0,1.0)
	//,bbox(-radius, radius, -radius, radius, -radius, radius)
{
	inv_area = 1.0 / (4 * PI*pow(radius, 2));
}

Sphere::~Sphere(void)
{

}

void Sphere::set_sampler(Sampler * _sampler)
{
	this->sampler_ptr = _sampler;
	this->sampler_ptr->map_samples_to_sphere();
	//this->sampler_ptr->map_samples_to_hemisphere(1);
}

Point3D Sphere::sample(void)
{
	Point3D sample_point = sampler_ptr->sample_sphere();
	//Point3D sample_point = sampler_ptr->sample_hemisphere();
	return(center + radius * sample_point);
}

float Sphere::pdf(ShadeRec & sr)
{
	return(inv_area);
}

Normal Sphere::get_normal(const Point3D & p)
{
	return(normal);
}

void Sphere::set_center(const Point3D& p)
{
	this->center = p;
}

void Sphere::set_radius(const double r)
{
	this->radius = r;
}

/*void Sphere::set_color(const RGBColor& color)
{
	this->color = color;
}*/

void Sphere::set_material(Material* material)
{
	this->material = material;
}

bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	if (!bbox.hit(ray))
		return (false);

	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d*ray.d;
	double b = 2.0*temp*ray.d;
	double c = temp * temp - radius * radius;
	double disc = b * b - 4.0*a*c;

	if (disc <= 0.0)
		return(false);
	else
	{
		double e = sqrt(disc);
		double denom = 2.0*a;
		t = (-b - e) / denom;

		if(t>kEpsilon)
		{
			tmin = t;
			//这里的矢量采用向量的三角形法则计算（相机与球心连线矢量+光线与碰撞点的连线矢量=碰撞点的法矢量）
			sr.normal = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return(true);
		}

		t = (-b + e) / denom;

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return(true);
		}
	}

	return(false);
}

bool Sphere::shadow_hit(const Ray & ray, float & tmin) const
{
	if (!bbox.hit(ray))
		return (false);

	if (!shadows)
		return(false);
	else
	{
		double t;
		Vector3D temp = ray.o - center;
		double a = ray.d*ray.d;
		double b = 2.0*temp*ray.d;
		double c = temp * temp - radius * radius;
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
}

BBox Sphere::get_bounding_box(void)
{
	double delta = 0.0001;
	bbox = BBox(center.x - radius - delta, center.x + radius + delta, center.y - radius - delta, center.y + radius + delta, center.z - radius - delta, center.z + radius + delta);
	return this->bbox;
}

BBox Sphere::set_bounding_box(void)
{
	this->bbox = get_bounding_box();
	return(this->bbox);
}
