#include "pch.h"
#include "Compound.h"

#include"World.h"
#include"Constants.h"

Compound::Compound(void)
	:GeometricObject()
{

}

Compound::~Compound(void)
{
	//delete_objects();
}

void Compound::set_material(Material * material_ptr)
{
	int num_objects = objects.size();
	for (int j = 0; j < num_objects; j++)
	{
		objects[j]->set_material(material_ptr);
	}
}

void Compound::add_object(GeometricObject * object_ptr)
{
	objects.push_back(object_ptr);
}

bool Compound::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double t;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		if (objects[j]->hit(ray, t, sr) && (t < tmin))
		{
			hit = true;
			tmin = t;
			GeometricObject::material = objects[j]->get_material();
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}
	if (hit)
	{
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return(hit);
}

bool Compound::shadow_hit(const Ray & ray, float & tmin) const
{
	float t;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		if (objects[j]->shadow_hit(ray, t) && (t < tmin))
		{
			hit = true;
			tmin = t;
		}
	}
	return(hit);
}

int Compound::get_num_objects(void)
{
	return(objects.size());
}

void Compound::delete_objects(void)
{
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		delete objects[j];
		objects[j] = nullptr;
	}
	objects.erase(objects.begin(), objects.end());
}