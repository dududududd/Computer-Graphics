#include "pch.h"
#include "Tracer.h"

Tracer::Tracer(void)
	:world_ptr(nullptr)
{

}

Tracer::Tracer(World* w_ptr)
	: world_ptr(w_ptr)
{

}

Tracer::Tracer(const Tracer& tracer)
	: world_ptr(tracer.world_ptr)
{

}

Tracer& Tracer::operator=(const Tracer& tracer)
{
	if (this == &tracer)
		return(*this);
	else
	{
		this->world_ptr = tracer.world_ptr;
		return(*this);
	}
}

Tracer::~Tracer(void)
{
	if (world_ptr != nullptr)
		world_ptr = nullptr;
}

RGBColor Tracer::trace_ray(const Ray& ray)const
{
	return(RGBColor(0.0));
}

RGBColor Tracer::trace_ray(const Ray ray, const int depth)const
{
	return(RGBColor(0.0));
}

RGBColor Tracer::trace_ray(const Ray ray, float& tmin, const int depth)const
{
	return(RGBColor(0.0));
}

