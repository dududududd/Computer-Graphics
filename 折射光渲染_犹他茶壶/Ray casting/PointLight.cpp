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
	return((location - sr.hit_point).hat());//��λ������������ɫ��---����Դ
}

bool PointLight::in_shadow(const Ray& ray, const ShadeRec & sr) const
{
	float t;
	int num_objects = sr.w.objects.size();
	float d = location.distance(ray.o);//�˴���d��������������������룬���Ա�������ײ���ڹ�Դ����ɫ��֮��������

	for (int j = 0; j < num_objects; j++)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
		{
			return(true);//������Ӱ����������ཻ���ҡ���ײ���ڹ�Դ����ɫ��֮�䡿������true
		}
	}
	return(false);
}

bool PointLight::casts_shadows()
{
	return(shadows);//�����û����õ���Ӱѡ��
}

RGBColor PointLight::L(ShadeRec& sr)//δ��Ӿ���˥��
{
	return(ls*color);
}

//RGBColor PointLight::L(ShadeRec& sr)//����˾���˥��
//{
//	double distance;//��P���Դλ�õľ���
//	distance = sqrt(pow(sr.hit_point.x - location.x, 2) + pow(sr.hit_point.y - location.y, 2) + pow(sr.hit_point.z - location.z, 2));
//	RGBColor L = (ls*color) / pow(distance, P);
//	return(L);
//}