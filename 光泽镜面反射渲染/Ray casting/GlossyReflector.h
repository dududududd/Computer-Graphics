#pragma once

#include"Phong.h"
#include"GlossySpecular.h"

class GlossyReflector:public Phong
{
public:

	GlossyReflector(void);

	virtual~GlossyReflector(void);

	void set_samples(const int num_samples, const float exp);

	void set_sampler(Sampler* sp, const float exp);

	void set_kr(const float k);

	void set_cr(const RGBColor& cs);

	void set_exponent(const float exp);

	virtual RGBColor area_light_shade(ShadeRec& sr);

private:

	GlossySpecular* glossy_specular_brdf;
};