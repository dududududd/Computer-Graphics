#pragma once

#include"Material.h"

#include"World.h"
#include"Lambertian.h"

class Matte:public Material
{
public:

	Matte(void);

	~Matte(void);

	void set_ka(const float k);

	void set_kd(const float k);

	void set_cd(const RGBColor& c);

	virtual RGBColor shade(ShadeRec& sr);

	virtual RGBColor area_light_shade(ShadeRec& sr);//其他对象接受区域光源所发射的辐射光渲染

	virtual RGBColor path_shade(ShadeRec& sr);

	virtual void set_sampler(Sampler* _sampler_ptr);

private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
};
/*
说明：
1.该类对环境光-漫反射着色的完全漫发射进行建模。
*/