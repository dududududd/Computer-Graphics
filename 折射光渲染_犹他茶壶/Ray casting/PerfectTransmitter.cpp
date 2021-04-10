#include"pch.h"
#include "PerfectTransmitter.h"
#include"Constants.h"

PerfectTransmitter::PerfectTransmitter(void)
	:BTDF(),
	kt(0.0),ior(1.0)
{
}

PerfectTransmitter::~PerfectTransmitter(void)
{
}

void PerfectTransmitter::set_kt(const float _kt)
{
	this->kt = _kt;
}

void PerfectTransmitter::set_ior(const float _ior)
{
	this->ior = _ior;
}

RGBColor PerfectTransmitter::f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wt) const
{
	return RGBColor();
}

RGBColor PerfectTransmitter::sample_f(const ShadeRec & sr, const Vector3D & wo, Vector3D & wt) const
{
	Normal n(sr.normal);
	float cos_thetai = n * wo;
	float eta = ior;

	if (cos_thetai < 0.0)
	{
		cos_thetai = -cos_thetai;
		n = -n;
		eta = 1.0 / eta;
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta*eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta)*n;

	return(kt / (eta*eta)*white / fabs(sr.normal*wt));
	//return(kt / (eta*eta)*skyblue / fabs(sr.normal*wt));
}

RGBColor PerfectTransmitter::rho(const ShadeRec & sr, const Vector3D & wo) const
{
	return RGBColor();
}

bool PerfectTransmitter::tir(const ShadeRec & sr) const
{
	Vector3D wo(-sr.ray.d);
	float cos_thetai = sr.normal*wo;
	float eta = ior;

	if (cos_thetai < 0.0)
		eta = 1.0 / eta;

	return(1.0 - (1.0 - cos_thetai * cos_thetai) / (eta*eta) < 0.0);
}