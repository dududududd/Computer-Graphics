#include "pch.h"
#include "Lambertian.h"

#include"World.h"


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

RGBColor Lambertian::sample_f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi, float & pdf) const
{
	Vector3D w =sr.normal;
	Vector3D v = Vector3D(0.0034, 1.0, 0.0071) ^ w;
	v.Normalize();
	Vector3D u = v ^ w;
	sampler_ptr->map_samples_to_hemisphere(1);
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x*u + sp.y*v + sp.z*w;
	wi.Normalize();
	pdf = sr.normal*wi*invPI;

	return(kd*cd*invPI);
}