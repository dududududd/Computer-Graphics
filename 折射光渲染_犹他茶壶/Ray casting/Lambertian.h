#pragma once

#include"BRDF.h"

class Lambertian:public BRDF//完全漫反射
{
public:

	Lambertian(void);

	~Lambertian(void);

	void set_kd(const float kd);

	void set_cd(const RGBColor& cd);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const;
	
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;
	
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const;

private:
	float kd;//漫反射系数
	RGBColor cd;//漫反射颜色值
};
/*
说明：
1.Ρd可表示为RGB颜色值，其可表示为Ρd=kd*cd;kd表示漫反射系数，cd表示为漫反射颜色值。
则BRDF可表示为f(r,d)=kd*cd/Π。
2.这里采用kd与cd乘积的形式表示Ρd的原因是便于用户对数据的修改。
3.Ρd的物理意义是：当BRDF与入射角和出射角无关时，定义了物体表面面片dA上方全部半球内部的反射通量与全部入射通量之比。
4.朗伯反射体定义为完全漫反射
5.对于完全漫发射的环境光照模型而言，通常采用双半球反射系数Ρhh表示。当入射辐射度具有同向性以及空间不变性时，该分数表示
全半球内的反射通量与全部入射通量之比。
*/
/*
说明：
1.所以，漫反射是主要用来模拟环境光的特征的。
*/