#include "pch.h"
#include "Phong.h"
#include"World.h"


Phong::Phong(void)
	:Material(), ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular)
{

}

Phong::~Phong(void)
{
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = nullptr;
	}
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = nullptr;
	}
	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = nullptr;
	}
}

void Phong::set_ka(const float ka)
{
	ambient_brdf->set_kd(ka);
}

void Phong::set_kd(const float kd)
{
	diffuse_brdf->set_kd(kd);
}

void Phong::set_cd(const RGBColor & c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

void Phong::set_ks(const float ks)
{
	specular_brdf->set_ks(ks);
}

void Phong::set_cs(const RGBColor & cs)
{
	specular_brdf->set_cs(cs);
}

void Phong::set_exp(const float exp)
{
	specular_brdf->set_exp(exp);
}

RGBColor Phong::shade(ShadeRec& sr)
{
	Vector3D wo = -sr.ray.d;//反射方向向量
	RGBColor L= ambient_brdf->rho(sr, wo)*sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();

	for (int j = 0; j < num_lights; j++)
	{
		Vector3D wi = sr.w.lights[j]->get_direction(sr);//入射方向向量
		float ndotwi = sr.normal*wi;

		if (ndotwi > 0.0)
		{
			if (!shadows)
				L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi))*sr.w.lights[j]->L(sr)*ndotwi;
			else
			{
				bool in_shadow = false;
				if (sr.w.lights[j]->casts_shadows())//判断用户是否开启阴影投射功能
				{
					Ray shadowRay(sr.hit_point, wi);//新建一个阴影光线，【光源：着色点，方向：着色点-》光源】
					in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);//使用阴影光线来判断着色点与光源之间是否存在碰撞点
				}//如果着色点在阴影区域中，将使用【环境光】进行着色

				if (!in_shadow)//如果着色点不在阴影区域内，将使用默认着色
				{
					L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi))*sr.w.lights[j]->L(sr)*ndotwi;
				}
			}
		}
	}
	return(L);
}

RGBColor Phong::area_light_shade(ShadeRec & sr)
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
				L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr, wo, wi) )*sr.w.lights[j]->L(sr)*sr.w.lights[j]->G(sr)*ndotwi / sr.w.lights[j]->pdf(sr);
				//L=[1/n]Σ(n)[f(p,ωi,ω0)Le(p',-ωi)V(p,p')G(p,p')]/p(p')
				//其中G(p,p')=[cosθicosθ']/||p'-p||²
				//这里因为只有一个区域光源，所以n=1
			}
		}
	}
	return(L);
}
