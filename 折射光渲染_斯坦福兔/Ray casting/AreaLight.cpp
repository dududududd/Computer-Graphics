#include "pch.h"
#include "AreaLight.h"

#include"World.h"

AreaLight::AreaLight(void)
	:Light(),object_ptr(nullptr),material_ptr(nullptr),
	light_normal(1.0),wi(1.0),sample_point(0.0)
{
}

AreaLight::~AreaLight(void)
{
}

void AreaLight::set_object(GeometricObject * _object_ptr)
{
	this->object_ptr = _object_ptr;
	this->material_ptr = _object_ptr->get_material();
}

Vector3D AreaLight::get_direction(ShadeRec& sr)
{
	sample_point = object_ptr->sample();
	light_normal = object_ptr->get_normal(sample_point);
	wi = sample_point - sr.hit_point;
	wi.Normalize();

	return(wi);
}

bool AreaLight::in_shadow(const Ray& ray, const ShadeRec & sr) const
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

RGBColor AreaLight::L(ShadeRec& sr)
{
	float ndotd = -light_normal * wi;

	if (ndotd > 0.0)
		return(material_ptr->get_Le(sr));
	else
	{
		return(RGBColor(0.0));
	}
}

float AreaLight::G(const ShadeRec& sr) const
{
	float ndotd = -light_normal * wi;//»ñµÃcos¦È'
	float d2 = sample_point.Distance_Square(sr.hit_point);
	
	return(ndotd / d2);
}

float AreaLight::pdf(ShadeRec& sr)
{
	return(object_ptr->pdf(sr));
}

bool AreaLight::casts_shadows()
{
	return shadows;
}
