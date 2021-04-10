#pragma once

#include"Tracer.h"

class RayCast:public Tracer
{
public:
	RayCast(void);

	RayCast(World* _worldptr);

	~RayCast(void);

	virtual RGBColor trace_ray(const Ray ray, const int depth)const;

};

