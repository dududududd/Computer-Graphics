#include "pch.h"
#include "Lambertian.h"

const double invPI = 0.3183098861837906715;

Lambertian::Lambertian(void)
	:BRDF(),kd(0.0),cd(RGBColor(0.0))
{

}

Lambertian::~Lambertian(void)
{

}

void Lambertian::set_kd(const float kd)
{
	this->kd = kd;
}

void Lambertian::set_cd(const RGBColor& cd)
{
	this->cd = cd;
}

RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const
{
	return(kd*cd*invPI);
}

RGBColor Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const
{
	return(1.0);//这里先随便定下一个值，否则会出现无法解析的错误
}

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3D& wo)const
{
	return(kd*cd);
}