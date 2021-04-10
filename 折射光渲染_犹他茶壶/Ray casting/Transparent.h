#pragma once

#include"Phong.h"
#include"PerfectTransmitter.h"

class Transparent:public Phong
{
public:

	Transparent(void);

	virtual~Transparent(void);

	void set_ior(const float _ior);

	void set_kr(const float _kr);

	void set_kt(const float _kt);

	virtual RGBColor shade(ShadeRec& sr);

private:

	PerfectSpecular* reflective_brdf;
	PerfectTransmitter* specular_brdf;
};

