#include"pch.h"
#include "GlossyReflector.h"

#include"World.h"

GlossyReflector::GlossyReflector(void)
	:Phong(), glossy_specular_brdf(new GlossySpecular)
{
}

GlossyReflector::~GlossyReflector(void)
{
	if (glossy_specular_brdf)
	{
		delete glossy_specular_brdf;
		glossy_specular_brdf = nullptr;
	}
}

void GlossyReflector::set_samples(const int num_samples, const float exp)
{
	glossy_specular_brdf->set_samples(num_samples, exp);
}

void GlossyReflector::set_sampler(Sampler * sp, const float exp)
{
	glossy_specular_brdf->set_sampler(sp, exp);
}

void GlossyReflector::set_kr(const float k)
{
	glossy_specular_brdf->set_ks(k);
}

void GlossyReflector::set_cr(const RGBColor& cs)
{
	glossy_specular_brdf->set_cs(cs);
}

void GlossyReflector::set_exponent(const float exp)
{
	glossy_specular_brdf->set_exp(exp);
}

RGBColor GlossyReflector::area_light_shade(ShadeRec & sr)
{
	RGBColor L(Phong::area_light_shade(sr));//Ö±½Ó¹âÕÕ
	Vector3D wo(-sr.ray.d);
	Vector3D wi;
	float pdf;
	RGBColor fr(glossy_specular_brdf->sample_f(sr, wo, wi, pdf));
	Ray reflected_ray(sr.hit_point, wi);
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*(sr.normal*wi) / pdf;

	return(L); 
}