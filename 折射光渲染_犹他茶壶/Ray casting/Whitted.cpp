#include "pch.h"
#include "Whitted.h"

#include"World.h"

Whitted::Whitted(void)
	:Tracer()
{
}

Whitted::Whitted(World * _world_ptr)
{
	this->world_ptr = _world_ptr;
}

Whitted::~Whitted(void)
{
}

RGBColor Whitted::trace_ray(const Ray ray, const int depth) const
{
	if (depth > world_ptr->vp.max_depth)
		return(RGBColor(0.0));
	else
	{
		ShadeRec sr(world_ptr->hit_objects(ray));
		if (sr.hit_an_object)
		{
			sr.depth = depth;
			sr.ray = ray;
			
			return(sr.material_ptr->shade(sr));
		}
		else
		{
			return(world_ptr->background_color);
		}
	}
}
