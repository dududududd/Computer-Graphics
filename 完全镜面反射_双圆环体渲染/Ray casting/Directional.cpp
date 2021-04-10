#include "pch.h"
#include "Directional.h"

#include"World.h"

Directional::Directional(void)
	:Light(),ls(1.0),color(1.0),dir(0,1,0)
{

}

Directional::~Directional(void)
{

}

void Directional::scale_radiance(const float b)
{
	this->ls = b;
}

void Directional::set_color(const RGBColor & color)
{
	this->color = color;
}

void Directional::set_direction(const Vector3D & v)
{
	this->dir = v;
	dir.Normalize();
}

Vector3D Directional::get_direction(ShadeRec& sr)
{
	return(dir);
}

RGBColor Directional::L(ShadeRec& sr)
{
	return(ls*color);
}

bool Directional::in_shadow(const Ray & ray, const ShadeRec & sr) const
{
	float t;
	int num_objects = sr.w.objects.size();
	float d = sr.hit_point.distance(dir);

	for (int j = 0; j < num_objects; j++)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
		{
			return(true);
		}
	}
	return(false);
}

bool Directional::casts_shadows()
{
	return shadows;
}
