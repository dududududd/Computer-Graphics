#pragma once

#include"BTDF.h"

class PerfectTransmitter:public BTDF
{
public:

	PerfectTransmitter(void);

	virtual~PerfectTransmitter(void);

	void set_kt(const float _kt);

	void set_ior(const float _ior);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt)const;

	//计算透视光线的方向并将其返回至参数wt中且仅适用于非全内反射条件下
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

	virtual bool tir(const ShadeRec& sr)const;

private:

	float kt;//Kt,透射系数∈[0,1]
	float ior;//η
};