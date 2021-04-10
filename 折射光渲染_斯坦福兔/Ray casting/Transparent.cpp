#include"pch.h"
#include "Transparent.h"

#include"World.h"

Transparent::Transparent(void)
	:Phong(),
	reflective_brdf(new PerfectSpecular),specular_brdf(new PerfectTransmitter)
{

}

Transparent::~Transparent(void)
{
}

void Transparent::set_ior(const float _ior)
{
	specular_brdf->set_ior(_ior);
}

void Transparent::set_kr(const float _kr)
{
	reflective_brdf->set_kr(_kr);
}

void Transparent::set_kt(const float _kt)
{
	specular_brdf->set_kt(_kt);
}

/*
 *说明：
 *当出现全内反射时，辐射度仅通过反射光线的返回值实现数量上的增加，无需乘以BRDF以及cosθi。
 *此时，也无需令BRDF使用Kr=1这一条件以及正常条件下以及正常情况下(无全内反射现象)的Kr值。
 */

RGBColor Transparent::shade(ShadeRec & sr)
{
	RGBColor L(Phong::shade(sr));

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);//computes wi
	Ray reflected_ray(sr.hit_point, wi);

	if (specular_brdf->tir(sr))
		L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
	    //kr=1.0
	else
	{
		Vector3D wt;
		RGBColor ft = specular_brdf->sample_f(sr, wo, wt);//computes wt
		Ray transmitted_ray(sr.hit_point, wt);

		L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*fabs(sr.normal*wi);

		L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1)*fabs(sr.normal*wt);
	}
	//以下为特殊处理，如果注释掉将产生红色图斑错误，具体分析可以为颜色中的R值变为了负值
	if (L.r < 0) L.r = 0;
	if (L.g < 0) L.g = 0;
	if (L.b < 0) L.b = 0;
	return(L);
}