#include "pch.h"
#include "GlossySpecular.h"
#include"ShadeRec.h"

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

void GlossySpecular::set_cs(const RGBColor & cs)
{
	this->cs = cs;
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

RGBColor GlossySpecular::rho(const ShadeRec& sr, const Vector3D& wo)const
{
	return(RGBColor(0.0));
}