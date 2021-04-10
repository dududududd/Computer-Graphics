#include "pch.h"
#include "AmbientOccluder.h"
#include"World.h"

AmbientOccluder::AmbientOccluder(void)
	:Light(),u(1.0, 0.0, 0.0), v(0.0, 1.0, 0.0), w(0.0, 0.0, 1.0),
	min_amount(0.05),ls(1.0),color(1.0),
	sampler_ptr(new MultiJittered)
{
}

AmbientOccluder::~AmbientOccluder(void)
{
}

void AmbientOccluder::scale_radiance(const float b)
{
	this->ls = b;
}

void AmbientOccluder::set_color(const RGBColor & color)
{
	this->color = color;
}

void AmbientOccluder::set_min_amount(const float amount)
{
	this->min_amount = amount;
}

void AmbientOccluder::set_sampler(Sampler * s_ptr)
{
	if (sampler_ptr)//�����Ѿ�����ͬ��ָ��
	{
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D AmbientOccluder::get_direction(ShadeRec& sr)
{
	Point3D sp = sampler_ptr->sample_hemisphere();
	return(sp.x*u + sp.y*v + sp.z*w);
}

bool AmbientOccluder::in_shadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int num_objects = sr.w.objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		if (sr.w.objects[j]->shadow_hit(ray, t))//��;�������ķֺţ������ҵ��Գ��򻷾��ڵ�һֱ���ڴ��������ϸ�����⣡����
		{
			return(true);
		}
	}

	return(false);
}

RGBColor AmbientOccluder::L(ShadeRec& sr)
{
	w = sr.normal;
	//���ߴ�ֱʱ���϶���ʸ��
	v = w ^ Vector3D(0.0072, 1.0, 0.0034);
	v.Normalize();
	u = v ^ w;

	Ray shadow_ray;
	shadow_ray.o = sr.hit_point;
	shadow_ray.d = get_direction(sr);

	if (!shadows)//�Ƿ����������ڵ�
		return(ls*color);
	else
	{
		if (in_shadow(shadow_ray, sr))
			return(min_amount*ls*color);//��������Ӱ��ɫ
		else
		{
			return(ls*color);//��������ɫ
		}
	}
}