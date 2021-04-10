#include "pch.h"
#include "GeometricObject.h"

#include"Normal.h"

GeometricObject::GeometricObject(void)
	://color(0.0)
	material(nullptr),shadows(true)
{

}

GeometricObject::GeometricObject(const GeometricObject& object)
	:// color(object.color)
	material(object.material),shadows(object.shadows)
{

}

GeometricObject& GeometricObject::operator=(const GeometricObject& geometricobject)
{
	if (this == &geometricobject)
		return(*this);
	else
	{
		//this->color = geometricobject.color;
		this->material = material;
		this->shadows = shadows;
		return(*this);
	}
}

GeometricObject::~GeometricObject(void)
{

}

/*RGBColor GeometricObject::get_color(void)
{
	return(this->color);
}*/

Material* GeometricObject::get_material(void)
{
	return(this->material);
}

bool GeometricObject::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	return false;
}

bool GeometricObject::shadow_hit(const Ray & ray, float & tmin) const
{
	return false;
}

Point3D GeometricObject::sample(void)
{
	return Point3D(0.0);
}

float GeometricObject::pdf(ShadeRec & sr)
{
	return 0.0f;
}

Normal GeometricObject::get_normal(const Point3D & p)
{
	return Normal();
}

Normal GeometricObject::get_normal(void) const
{
	return Normal();
}

void GeometricObject::set_material(Material * material_ptr)
{
	this->material = material_ptr;
}

BBox GeometricObject::get_bounding_box(void)
{
	return BBox();
}

BBox GeometricObject::set_bounding_box(void)
{
	return BBox();
}

void GeometricObject::add_object(GeometricObject * object_ptr)
{
}
