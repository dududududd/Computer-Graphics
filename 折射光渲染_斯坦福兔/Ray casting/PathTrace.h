#pragma once

#include"Tracer.h"

class PathTrace:public Tracer
{
public:

	PathTrace(void);

	PathTrace(World* _world_ptr);

	virtual~PathTrace(void);

	virtual RGBColor trace_ray(const Ray ray, const int depth)const;

};
/*
说明：
1.目前这里所实现的路径跟踪仅限于Lambertian材质以及完全镜面反射。
*/
