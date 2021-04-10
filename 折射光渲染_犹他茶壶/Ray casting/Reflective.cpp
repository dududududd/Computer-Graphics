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
RGBColor Reflective::area_light_shade(ShadeRec & sr)
{
	RGBColor L(Phong::shade(sr));//直接照明

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
	Ray reflected_ray(sr.hit_point, wi);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*(sr.normal*wi);

	return(L);
}
RGBColor Reflective::path_shade(ShadeRec & sr)
{
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	float pdf;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi, pdf);
	Ray reflected_ray(sr.hit_point, wi);

	return(fr*sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*(sr.normal*wi) / pdf);
}
/*
说明：
这里，trace_ray()函数参数"sr.depth+1"中的"+1"项，
该方案提供了递归程序设计时常会用到的一类规避机制。
*/
/*
说明：
这里，你会发现shade函数和area_light_shade函数是相同的，原因是当我们在渲染一个场景时，场景中如果只是存在的一种材质，
那么所有材质都会调用同一函数，这显然是没问题的。但是当我们去渲染一个包含多种材质的场景时，只对一种材质实施渲染显然是
不合理的。所以，同一所有材质的渲染函数是很有必要的。这里，添加新的跟踪器来或者在跟踪器中去判断材质的类型并不是一种好的方法，
所以，为方便材质渲染的通用性，我建议将所有的材质类都设置area_light_shade函数，从而同一的材质的渲染函数。
*/
