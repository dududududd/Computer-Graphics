#include "pch.h"
#include "SolidCylinder.h"

#include"Disk.h"
#include"OpenCylinder.h"

SolidCylinder::SolidCylinder(void)
	:Compound()
{
}

SolidCylinder::SolidCylinder(const SolidCylinder & cc)
{
}

SolidCylinder::SolidCylinder(const float bottom, const float top, const float radius)
	:Compound()
{
	objects.push_back(new Disk(Point3D(0, bottom, 0), radius, Normal(0, -1, 0)));

	objects.push_back(new Disk(Point3D(0, top, 0), radius, Normal(0, 1, 0)));

	objects.push_back(new OpenCylinder(bottom, top, radius));
}

SolidCylinder::~SolidCylinder(void)
{
}

bool SolidCylinder::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	if (bbox.hit(ray))
		return(Compound::hit(ray, tmin, sr));
	else 
	{
		return(false);
	}
}

BBox SolidCylinder::get_bounding_box(void)
{
	double delta = 0.0001;
	int objects_num = objects.size();
	for (int i = 0; i < objects_num; i++)
	{
		BBox temp = objects[i]->get_bounding_box();
		if (bbox.x0 > temp.x0)
			bbox.x0 = temp.x0;
		if (bbox.y0 > temp.y0)
			bbox.y0 = temp.y0;
		if (bbox.z0 > temp.z0)
			bbox.z0 = temp.z0;
		if (bbox.x1 < temp.x1)
			bbox.x1 = temp.x1;
		if (bbox.y1 < temp.y1)
			bbox.y1 = temp.y1;
		if (bbox.z1 < temp.z1)
			bbox.z1 = temp.z1;
	}
	return(this->bbox);
}

BBox SolidCylinder::set_bounding_box(void)
{
	this->bbox = get_bounding_box();
	return(this->bbox);
}