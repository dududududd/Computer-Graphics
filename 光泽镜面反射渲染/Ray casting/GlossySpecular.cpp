#include "pch.h"
#include "GlossySpecular.h"
#include"ShadeRec.h"

#include"MultiJittered.h"

GlossySpecular::GlossySpecular(void)
	:BRDF(),ks(0.0),cs(1.0),exp(1.0)
{

}

GlossySpecular::~GlossySpecular(void)
{

}

void GlossySpecular::set_ks(const float ks)
{
	this->ks = ks;
}

void GlossySpecular::set_exp(const float exp)
{
	this->exp = exp;
}

void GlossySpecular::set_samples(const int _num_samples, const float _exp)
{
	this->sampler_ptr = new MultiJittered(_num_samples);
	this->sampler_ptr->map_samples_to_hemisphere(_exp);
}

void GlossySpecular::set_cs(const RGBColor & cs)
{
	this->cs = cs;
}

void GlossySpecular::set_sampler(Sampler * sp, const float exp)
{
	this->sampler_ptr = sp;
	this->sampler_ptr->map_samples_to_hemisphere(exp);
}

RGBColor GlossySpecular::f(const ShadeRec & sr, const Vector3D & wi, const Vector3D & wo) const
{
	/*RGBColor L;
	float ndotwi = sr.normal*wi;
	Vector3D r(-wi + 2.0*sr.normal*ndotwi);
	float rdotwo = r * wo;
	if (rdotwo > 0.0)
		L = ks * pow(rdotwo, exp)*cs;

	return(L);*/

	/*Blinn修改Phong镜面模型*/
	RGBColor L;
	Vector3D v = wi + wo;
	Vector3D h = v / sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	float ndoth = sr.normal*h;
	if (ndoth > 0.0)
	{
		L = ks * pow(ndoth, exp);
	}
	return(L);
}

RGBColor GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const
{
	return RGBColor(0.0);//暂且默认为黑色，否则会出现无法解析的错误
}

RGBColor GlossySpecular::sample_f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wi, float & pdf) const
{
	float ndotwo = sr.normal*wo;
	Vector3D r = -wo + 2.0*sr.normal*ndotwo;//镜面反射方向

	Vector3D w = r;
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.Normalize();
	Vector3D v = u ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x*u + sp.y*v + sp.z*w;//反射光方向

	if (sr.normal*wi < 0.0)//反射光线在表面下方
	{
		wi = -sp.x*u - sp.y*v + sp.z*w;
	}

	float phong_lobe = pow(r*wi, exp);
	pdf = phong_lobe * (sr.normal*wi);

	return(ks*cs*phong_lobe);
}

RGBColor GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo)const
{
	return(black);
}