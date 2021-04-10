#include "pch.h"
#include "ShadeRec.h"
#include"World.h"

ShadeRec::ShadeRec(World& wr)
	:hit_an_object(false), material_ptr(nullptr),
	local_hit_point(), hit_point(),
	normal(), ray(),depth(0),t(0.0),
	color(RGBColor(0.0)), dir(),
	w(wr)
{

}

ShadeRec::ShadeRec(const ShadeRec& sr)
	:hit_an_object(sr.hit_an_object),material_ptr(sr.material_ptr),
	local_hit_point(sr.local_hit_point),hit_point(sr.hit_point),
	normal(sr.normal),ray(sr.ray),depth(sr.depth),
	color(sr.color),dir(sr.dir),t(sr.t),
	w(sr.w)
{

}

ShadeRec::~ShadeRec(void)
{

}

ShadeRec& ShadeRec::operator=(const ShadeRec& rhs)
{
	if (this == &rhs)
		return(*this);
	else
	{
		this->hit_an_object = rhs.hit_an_object;
		this->local_hit_point = rhs.local_hit_point;
		this->normal = rhs.normal;
		this->color = rhs.color;
		this->w = rhs.w;
		this->depth = rhs.depth;
		this->dir = rhs.dir;
		this->hit_point = rhs.hit_point;
		this->material_ptr = rhs.material_ptr;
		this->t = t;
		this->ray = ray;
		return(*this);
	}
}