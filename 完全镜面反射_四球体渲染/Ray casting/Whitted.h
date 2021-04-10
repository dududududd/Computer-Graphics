#pragma once

#include"Tracer.h"

class Whitted:public Tracer
{
public:
	Whitted(void);

	Whitted(World* _world_ptr);

	virtual~Whitted(void);

	virtual RGBColor trace_ray(const Ray ray, const int depth)const;

};