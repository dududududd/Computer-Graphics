#include "pch.h"
#include "PointLight.h"

#include"World.h"

PointLight::PointLight(void)
	:Light(), ls(1.0), color(0.0), location(0.0, 1.0, 0.0)
{

}

PointLight::~PointLight(void)
{

}

void PointLight::set_location(const double a, const double b, const double c)
{
	this->location = Vector3D(a, b, c);
}

void PointLight::set_color(const RGBColor & color)
{
	this->color = color;
}

void PointLight::scale_radiance(const float b)
{
	this->ls = b;
}

//void PointLight::set_Attenuation_factor(const int P)
//{
//	this->P = P;
//}

Vector3D PointLight::get_direction(ShadeRec& sr)
{
	return((location - sr.hit_point).hat());//单位方向向量：着色点---》光源
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec & sr) const
{
	float t;
	int num_objects = sr.w.objects.size();
	float d = location.distance(ray.o);//此处的d不代表方向向量而代表距离，用以保留【碰撞点在光源与着色点之间的情况】

	for (int j = 0; j < num_objects; j++)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
		{
			return(true);//当【阴影光线与对象相交】且【碰撞点在光源与着色点之间】，返回true
		}
	}
	return(false);
}

bool PointLight::casts_shadows()
{
	return(shadows);//返回用户设置的阴影选项
}

RGBColor PointLight::L(ShadeRec& sr)//未添加距离衰减
{
	return(ls*color);
}

//RGBColor PointLight::L(ShadeRec& sr)//添加了距离衰减
//{
//	double distance;//点P与光源位置的距离
//	distance = sqrt(pow(sr.hit_point.x - location.x, 2) + pow(sr.hit_point.y - location.y, 2) + pow(sr.hit_point.z - location.z, 2));
//	RGBColor L = (ls*color) / pow(distance, P);
//	return(L);
//}