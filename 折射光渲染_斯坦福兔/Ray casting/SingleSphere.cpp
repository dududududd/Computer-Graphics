#include "pch.h"
#include "SingleSphere.h"

SingleSphere::SingleSphere(void)
	:Tracer()
{

}

SingleSphere::~SingleSphere(void)
{

}

SingleSphere::SingleSphere(World* _worldPtr)
	:Tracer(_worldPtr)
{

}

//RGBColor SingleSphere::trace_ray(const Ray& ray)const
//{
//	ShadeRec sr(*world_ptr);
//	double t;
//
//	if (world_ptr->sphere.hit(ray, t, sr))
//		return(RGBColor(1.0, 0.0, 0.0));//返回一个红色球体
//	else
//	{
//		return(RGBColor(0.0));
//	}
//}