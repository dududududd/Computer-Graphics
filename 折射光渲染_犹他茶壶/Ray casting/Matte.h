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

	virtual RGBColor area_light_shade(ShadeRec& sr);//����������������Դ������ķ������Ⱦ

	virtual RGBColor path_shade(ShadeRec& sr);

	virtual void set_sampler(Sampler* _sampler_ptr);

private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
};
/*
˵����
1.����Ի�����-��������ɫ����ȫ��������н�ģ��
*/