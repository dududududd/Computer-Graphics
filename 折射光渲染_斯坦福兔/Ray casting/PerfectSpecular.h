#pragma once

#include"BRDF.h"

class PerfectSpecular:public BRDF
{
public:
	PerfectSpecular(void);

	~PerfectSpecular(void);

	void set_kr(const float _kr);

	void set_cr(const RGBColor& cr);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const;

private:
	float kr;
	RGBColor cr;
};
/*
1.对于镜面反射，其不具备双半球反射的性质，所以其rho()函数返回背景颜色
*/