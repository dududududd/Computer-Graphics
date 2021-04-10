#pragma once

#include"RGBColor.h"
#include"Vector3D.h"
class ShadeRec;
class Sampler;

class BRDF
{
public:
	BRDF(void);

	BRDF(const BRDF& brdf);

	BRDF& operator=(const BRDF& brdf);

	virtual~BRDF(void);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const = 0;//计算发射光的方向

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const;

	virtual void set_sampler(Sampler* _sampler_ptr);

protected:

	Sampler* sampler_ptr;
};
/*
说明：
1.如果函数f()不包含delta函数，将返回BRDF自身。
2.针对于反射材质以及漫发射-漫发射光线模拟计算，函数sample_f()用于计算反射光线的方向。但是，需要注意的是，
函数sample_f（）中的参数ωi用于返回最终的方向，因而不可为常量。其相关方向将通过对BRDF采样计算得到，这也是BRDF基类包含一个采样器对象指针的原因。
3.函数rho()将返回双半球反射系数Ρhh，其中，双半球反射系数指环境光的漫发射：入射光来自于半球，反射光同样是半球。
*/
/*
1.f()函数用于计算BRDF
2.通过材质特性表示物体表面的反射特征是光线跟踪计算中的一种常见计算方法。
*/