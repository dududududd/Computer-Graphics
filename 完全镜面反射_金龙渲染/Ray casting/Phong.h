#pragma once

#include"Material.h"
#include"GlossySpecular.h"
#include"Lambertian.h"

class Phong:public Material
{
public:
	
	Phong(void);

	~Phong(void);

	void set_ka(const float ka);//���û�����������ϵ��

	void set_kd(const float kd);//�����������������ϵ��

	void set_cd(const RGBColor& c);//�������������ɫ

	void set_ks(const float ks);//���þ��淴��ⷴ��ϵ��

	void set_cs(const RGBColor& cs);//���þ��淴�����ɫ

	void set_exp(const float exp);//����Phongָ��

	virtual RGBColor shade(ShadeRec& sr);

	virtual RGBColor area_light_shade(ShadeRec& sr);

protected:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

