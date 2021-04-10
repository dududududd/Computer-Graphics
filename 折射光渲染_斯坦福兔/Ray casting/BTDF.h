#pragma once

#include"ShadeRec.h"

class BTDF
{
public:

	BTDF(void);

	virtual~BTDF(void);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt)const = 0;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const = 0;

	virtual bool tir(const ShadeRec& sr)const = 0;

private:

};
/*
 *注意：
 *这里tir()函数用于检测全内反射
 */
