#include "pch.h"
#include "Matte.h"

Matte::Matte(void)
	:Material(), ambient_brdf(new Lambertian), diffuse_brdf(new Lambertian)
{

}

Matte::~Matte(void)
{
	if (ambient_brdf != nullptr) {
		delete ambient_brdf;
		ambient_brdf = nullptr;
	}
	if (diffuse_brdf != nullptr) {
		delete diffuse_brdf;
		diffuse_brdf = nullptr;
	}
}

void Matte::set_ka(const float ka)
{
	ambient_brdf->set_kd(ka);
}

void Matte::set_kd(const float kd)
{
	diffuse_brdf->set_kd(kd);
}

void Matte::set_cd(const RGBColor& c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

RGBColor Matte::shade(ShadeRec& sr)
{
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo)*sr.w.ambient_ptr->L(sr);
	int numLights = sr.w.lights.size();

	for (int j = 0; j < numLights; j++)
	{
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal*wi;

		if (ndotwi > 0.0)
		{
			if (!shadows)
				L += diffuse_brdf->f(sr, wo, wi)*sr.w.lights[j]->L(sr)*ndotwi;
			else
			{
				bool in_shadow = false;
				if (sr.w.lights[j]->casts_shadows())
				{
					Ray shadowRay(sr.hit_point, wi);
					in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
				}

				if (!in_shadow)
				{
					L += diffuse_brdf->f(sr, wo, wi)*sr.w.lights[j]->L(sr)*ndotwi;
				}
			}
		}
	}
	return(L);
}

RGBColor Matte::area_light_shade(ShadeRec& sr)
{
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo)*sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();

	for (int j = 0; j < num_lights; j++)
	{
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal*wi;

		if (ndotwi > 0.0)
		{
			bool in_shadow = false;

			if (sr.w.lights[j]->casts_shadows())//用于计算V(p,p')函数
			{
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
			{
				L += diffuse_brdf->f(sr, wo, wi)*sr.w.lights[j]->L(sr)*sr.w.lights[j]->G(sr)*ndotwi / sr.w.lights[j]->pdf(sr);
				//L=[1/n]Σ(n)[f(p,ωi,ω0)Le(p',-ωi)V(p,p')G(p,p')]/p(p')
				//其中G(p,p')=[cosθicosθ']/||p'-p||²
				//这里因为只有一个区域光源，所以n=1
			}
		}
	}
	return(L);
}

RGBColor Matte::path_shade(ShadeRec & sr)
{
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	RGBColor f = diffuse_brdf->sample_f(sr, wo, wi, pdf);
	float ndotwi = sr.normal*wi;
	Ray reflected_ray(sr.hit_point, wi);

	return(f*sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*ndotwi / pdf);
}

void Matte::set_sampler(Sampler * _sampler_ptr)
{
	this->diffuse_brdf->set_sampler(_sampler_ptr);
}
