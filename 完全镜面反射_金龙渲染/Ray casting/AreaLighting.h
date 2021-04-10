#pragma once

#include"Tracer.h"

class AreaLighting:public Tracer
{
public:
	AreaLighting(void);

	AreaLighting(World* _worldptr);

	~AreaLighting(void);

	virtual RGBColor trace_ray(const Ray ray, const int depth)const;
};

