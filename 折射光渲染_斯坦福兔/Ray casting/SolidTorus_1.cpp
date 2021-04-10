#include "SolidTorus_1.h"

#include"Torus_1.h"
#include"OpenCylinder1.h"
#include"OpenCylinder2.h"

SolidTorus_1::SolidTorus_1(void)
	:Compound(), bbox(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)
{

}

SolidTorus_1::SolidTorus_1(const float bottom, const float top, const float Radius, const float radius)
	:Compound()
{
	//外部凸空心圆柱
	//法向量全部朝外
	objects.push_back(new OpenCylinder1(bottom, top, Radius));

	//内部凹空心圆柱
	//法向量全部朝内
	objects.push_back(new OpenCylinder2(bottom, top, radius));

	objects.push_back(new Torus_1(Point3D(0.0, top, 0.0), radius, Radius, Normal(0, 1, 0)));

	objects.push_back(new Torus_1(Point3D(0.0, bottom, 0.0), radius, Radius, Normal(0, -1, 0)));

	//构造包围盒
	bbox.x0 = -Radius; bbox.x1 = Radius;
	bbox.y0 = bottom; bbox.y1 = top;
	bbox.z0 = -Radius; bbox.z1 = Radius;
}

SolidTorus_1::~SolidTorus_1(void)
{

}

bool SolidTorus_1::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	if (bbox.hit(ray))
		return(Compound::hit(ray, tmin, sr));
	else
	{
		return(false);
	}
}

bool SolidTorus_1::shadow_hit(const Ray & ray, float & tmin) const
{
	if (bbox.hit(ray))
	{
		return(Compound::shadow_hit(ray, tmin));
	}
	else
	{
		return(false);
	}
}

void SolidTorus_1::set_outer_wall_material(Material * material_ptr)
{
	objects[0]->set_material(material_ptr);
}

void SolidTorus_1::set_inner_wall_material(Material * material_ptr)
{
	objects[1]->set_material(material_ptr);
}

void SolidTorus_1::set_top_material(Material * material_ptr)
{
	objects[2]->set_material(material_ptr);
}

void SolidTorus_1::set_bottom_material(Material * material_ptr)
{
	objects[3]->set_material(material_ptr);
}

BBox SolidTorus_1::get_bounding_box(void)
{
	double delta = 0.0001;
	int num_objects = objects.size();

	for (int i = 0; i < num_objects; i++)
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

BBox SolidTorus_1::set_bounding_box(void)
{
	this->bbox = get_bounding_box();
	return(this->bbox);
}