#include "pch.h"
#include "Reflective.h"

#include"World.h"

Reflective::Reflective(void)
	:Phong(), reflective_brdf(new PerfectSpecular)
{
}

Reflective::~Reflective(void)
{
}

void Reflective::set_kr(const float _kr)
{
	reflective_brdf->set_kr(_kr);
}

void Reflective::set_cr(const RGBColor & _cr)
{
	reflective_brdf->set_cr(_cr);
}

RGBColor Reflective::shade(ShadeRec & sr)
{
	RGBColor L(Phong::shade(sr));//直接照明

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflected_ray(sr.hit_point, wi);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*(sr.normal*wi);

	return(L);
}
/*
说明：
这里，trace_ray()函数参数"sr.depth+1"中的"+1"项，
该方案提供了递归程序设计时常会用到的一类规避机制。
*/
