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
˵����
1.Ŀǰ������ʵ�ֵ�·�����ٽ�����Lambertian�����Լ���ȫ���淴�䡣
*/
