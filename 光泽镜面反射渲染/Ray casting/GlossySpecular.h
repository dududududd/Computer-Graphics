#pragma once

#include"BRDF.h"

class GlossySpecular:public BRDF
{
public:

	GlossySpecular(void);

	~GlossySpecular(void);

	void set_ks(const float ks);

	void set_exp(const float exp);

	void set_cs(const RGBColor& cs);//设置有色高光

	void set_sampler(Sampler* sp, const float exp);//任何类型的采样

	void set_samples(const int num_smaples, const float exp);//多重抖动采样

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

private:
	float ks;//镜面反射系数
	RGBColor cs;//镜面颜色值
	float exp;//即e
};