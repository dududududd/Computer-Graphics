#include "pch.h"
#include "EnvironmentLight.h"

#include"World.h"

EnvironmentLight::EnvironmentLight(void)
	:Light(), material_ptr(nullptr), sampler_ptr(nullptr),
	u(1.0, 0.0, 0.0), v(0.0, 1.0, 0.0), w(0.0, 0.0, 1.0),
	wi(1.0, 0.0, 0.0)
{
}

EnvironmentLight::~EnvironmentLight(void)
{
}

void EnvironmentLight::set_sampler(Sampler * sampler)
{
	this->sampler_ptr = sampler;
	sampler_ptr->map_samples_to_hemisphere(1);
}

void EnvironmentLight::set_material(Material * material)
{
	this->material_ptr = material;
}

Vector3D EnvironmentLight::get_direction(ShadeRec & sr)
{
	w = sr.normal;
	v = Vector3D((0.0034, 1, 0.0071)) ^ w;
	v.Normalize();
	u = v ^ w;
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x*u + sp.y*v + sp.z*w;//坐标为碰撞点，由碰撞点到半球体采样点方向的光线

	return(wi);
}

RGBColor EnvironmentLight::L(ShadeRec & sr)
{
	return(material_ptr->get_Le(sr));
}

bool EnvironmentLight::in_shadow(const Ray & ray, const ShadeRec & sr) const
{
	float t;
	int num_objects = sr.w.objects.size();
	float ts = (sample_point - ray.o)*ray.d;

	for (int j = 0; j < num_objects; j++)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < ts)
		{
			return(true);
		}
	}
	return(false);
}

float EnvironmentLight::pdf(ShadeRec & sr)
{
	return((sr.normal*wi) / PI);
}