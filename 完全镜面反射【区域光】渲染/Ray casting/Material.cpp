#include "pch.h"
#include "Material.h"

Material::Material(void)
	:shadows(true)
{

}

Material::~Material(void)
{

}

RGBColor Material::shade(ShadeRec& sr)
{
	return(RGBColor(0.0));
}

RGBColor Material::area_light_shade(ShadeRec & sr)
{
	return RGBColor(0.0);
}

RGBColor Material::get_Le(ShadeRec & sr) const
{
	return RGBColor(0.0);
}
