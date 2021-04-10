#pragma once

#include"Material.h"
#include"GlossySpecular.h"
#include"Lambertian.h"

class Phong:public Material
{
public:
	
	Phong(void);

	~Phong(void);

	void set_ka(const float ka);//设置环境光漫反射系数

	void set_kd(const float kd);//设置漫反射光漫反射系数

	void set_cd(const RGBColor& c);//设置漫反射光颜色

	void set_ks(const float ks);//设置镜面反射光反射系数

	void set_cs(const RGBColor& cs);//设置镜面反射光颜色

	void set_exp(const float exp);//设置Phong指数

	virtual RGBColor shade(ShadeRec& sr);

	virtual RGBColor area_light_shade(ShadeRec& sr);

protected:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

