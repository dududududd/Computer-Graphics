#include "pch.h"
#include "Ambient.h"

Ambient::Ambient(void)
	:Light(), ls(1.0), color(1.0)
{

}

Ambient::~Ambient(void)
{

}

void Ambient::scale_radiance(const float b)
{
	ls = b;
}

void Ambient::set_color(const RGBColor & color)
{
	this->color = color;
}

Vector3D Ambient::get_direction(ShadeRec& sr)
{
	return(Vector3D(0.0));
}

RGBColor Ambient::L(ShadeRec& sr)
{
	return(ls*color);
}

bool Ambient::in_shadow(const Ray & ray, const ShadeRec & sr) const
{
	return false;//这里我认为环境光一般不参与阴影运算
}
