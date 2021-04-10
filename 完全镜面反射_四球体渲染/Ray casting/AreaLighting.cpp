#include "pch.h"
#include "AreaLighting.h"

#include"World.h"
#include"ShadeRec.h"

AreaLighting::AreaLighting(void)
	:Tracer()
{

}

AreaLighting::AreaLighting(World* _worldptr)
	: Tracer(_worldptr)
{

}

AreaLighting::~AreaLighting(void)
{

}

RGBColor AreaLighting::trace_ray(const Ray ray, const int depth)const
{
	ShadeRec sr(world_ptr->hit_objects(ray));

	if (sr.hit_an_object)
	{
		sr.ray = ray;
		return(sr.material_ptr->shade(sr));
	}
	else
	{
		return(world_ptr->background_color);
	}
}