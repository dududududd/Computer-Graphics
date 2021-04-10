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
�������ײ��⺯������3�ַ�ʽ���㲢������Ӧ����ײ��Ϣ��
�������ز�������ʱ���������жϹ����Ƿ����������ײ��
ͨ������tmin���������ײ��(������)�Ĺ��߲�����
����ShadeRec�����������������Ϣ��
*/