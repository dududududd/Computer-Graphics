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

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

private:
	float ks;//镜面反射系数
	RGBColor cs;//镜面颜色值
	float exp;//即e
};