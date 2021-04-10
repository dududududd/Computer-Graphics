#include "pch.h"
#include "Light.h"


Light::Light(void)
	:shadows(false)
{

}

Light::~Light(void)
{

}

bool Light::casts_shadows()
{
	return shadows;
}

float Light::G(const ShadeRec & sr) const
{
	return 1.0f;
}

float Light::pdf(ShadeRec & sr)
{
	return 1.0f;
}

