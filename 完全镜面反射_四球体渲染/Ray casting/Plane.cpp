#include "pch.h"
#include "Plane.h"
#include"ShadeRec.h"

const double Plane::kEpsilon = 0.001;

Plane::Plane(void)
	:GeometricObject(),point(0.0),normal(0.0,1.0,0.0)
{
	
}

Plane::Plane(const Point3D& p, Normal& n)
	: GeometricObject(), point(p), normal(n)
{
	n.Normalize();
}

Plane::~Plane(void)
{

}

//void Plane::set_color(const RGBColor& color)
//{
//	this->color = color;
//}

void Plane::set_material(Material* material)
{
	this->material = material;
}

bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	double t = (point - ray.o)*normal / (ray.d*normal);
	if (t > kEpsilon)
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o + tmin * ray.d;

		return(true);
	}
	else
	{
		return(false);
	}
}

bool Plane::shadow_hit(const Ray& ray, float& tmin) const
{
	if (!shadows)
		return(false);
	else
	{
		float t = (point - ray.o)*normal / (ray.d*normal);

		if (t > kEpsilon)
		{
			tmin = t;
			return(true);
		}
		else
		{
			return(false);
		}
	}	
}
/*
对象的碰撞检测函数将以3种方式计算并返回相应的碰撞信息：
当仅返回布尔类型时，函数将判断光线是否与对象发生碰撞；
通过参数tmin返回最近碰撞点(若存在)的光线参数；
返回ShadeRec对象参数所需的相关信息。
*/