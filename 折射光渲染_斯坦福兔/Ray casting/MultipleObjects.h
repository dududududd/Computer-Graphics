#pragma once

#include"Tracer.h"
#include"ShadeRec.h"

class MultipleObjects:public Tracer
{
public:
	MultipleObjects(void);
	MultipleObjects(World* _worldPtr);

	~MultipleObjects(void);
	virtual RGBColor trace_ray(const Ray& ray)const;
	virtual RGBColor trace_ray(const Ray& ray, const int depth)const;
};