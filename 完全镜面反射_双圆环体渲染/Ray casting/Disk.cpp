#include "pch.h"
#include "Disk.h"

#include"ShadeRec.h"

const double PI = 3.1415926535897932384;
const double Disk::kEpsilon = 0.001;

Disk::Disk(void)
	:GeometricObject(),center(0.0,0.0,0.0),radius(1.0),normal(0.0,1.0,0.0)
	,sampler_ptr(nullptr),bbox()
{
	inv_area = 1.0 / (PI * pow(radius, 2));
}

Disk::~Disk(void)
{

}

Disk::Disk(const Point3D& _center, const double _radius, const Normal& _n)
	:GeometricObject(),center(_center),radius(_radius),normal(_n),bbox()
{
	inv_area = 1.0 / (PI*pow(radius, 2));
	normal.Normalize();
	this->sampler_ptr = nullptr;
}

void Disk::set_sampler(Sampler* sampler)
{
	this->sampler_ptr = sampler;
	sampler_ptr->map_samples_to_unit_disk();
}

bool Disk::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	float t = (center - ray.o)*normal / (ray.d*normal);

	if (t <= kEpsilon)
		return(false);

	Point3D p = ray.o + t * ray.d;
	double r_squared = pow(radius, 2.0);

	if (center.Distance_Square(p) < r_squared)
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = p;

		return(true);
	}
	else
	{
		return(false);
	}
}

Point3D Disk::sample(void)
{
	compute_uvw();
	Point2D sample_point = sampler_ptr->sample_unit_disk();
	return(center + radius * (sample_point.x*u + sample_point.y*v));
}

float Disk::pdf(ShadeRec& sr)
{
	return (inv_area);
}

Normal Disk::get_normal(const Point3D& p)
{
	return(this->normal);
}

void Disk::set_material(Material* material_ptr)
{
	this->material = material_ptr;
}

void Disk::compute_uvw(void)
{
	Vector3D up(0.0, 1.0, 0.0);
	w = normal;
	v = w ^ up;
	v.Normalize();
	u = w ^ v;
}

BBox Disk::get_bounding_box(void)
{
	double delta = 0.0001;
	bbox = BBox(center.x - radius - delta, center.x + radius + delta, center.y - delta, center.y + delta, center.z - radius - delta, center.z + radius + delta);
	return(this->bbox);
}

BBox Disk::set_bounding_box(void)
{
	bbox = get_bounding_box();
	return(this->bbox);
}

