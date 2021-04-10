#include "pch.h"
#include "PerfectSpecular.h"

#include"ShadeRec.h"

PerfectSpecular::PerfectSpecular(void)
	:BRDF(), kr(0.0), cr(1.0)
{

}

PerfectSpecular::~PerfectSpecular(void)
{

}

void PerfectSpecular::set_kr(const float _kr)
{
	this->kr = _kr;
}

void PerfectSpecular::set_cr(const RGBColor & cr)
{
	this->cr = cr;
}

RGBColor PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const
{
	return(RGBColor(0.0));//ºÚÉ«
}

RGBColor PerfectSpecular::sample_f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi) const
{
	float ndotwo = sr.normal*wo;
	wi = -wo + 2.0*sr.normal*ndotwo;

	return(kr*cr / (sr.normal*wi));
}

RGBColor PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo)const
{
	return(RGBColor(0.0));//ºÚÉ«
}

RGBColor PerfectSpecular::sample_f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi, float & pdf) const
{
	float ndotwo = sr.normal*wo;
	wi = -wo + 2.0*sr.normal*ndotwo;
	pdf = sr.normal*wi;

	return(kr*cr);
}
