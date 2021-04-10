#include"pch.h"
#include "Transparent.h"

#include"World.h"

Transparent::Transparent(void)
	:Phong(),
	reflective_brdf(new PerfectSpecular),specular_brdf(new PerfectTransmitter)
{

}

Transparent::~Transparent(void)
{
}

void Transparent::set_ior(const float _ior)
{
	specular_brdf->set_ior(_ior);
}

void Transparent::set_kr(const float _kr)
{
	reflective_brdf->set_kr(_kr);
}

void Transparent::set_kt(const float _kt)
{
	specular_brdf->set_kt(_kt);
}

/*
 *˵����
 *������ȫ�ڷ���ʱ������Ƚ�ͨ��������ߵķ���ֵʵ�������ϵ����ӣ��������BRDF�Լ�cos��i��
 *��ʱ��Ҳ������BRDFʹ��Kr=1��һ�����Լ������������Լ����������(��ȫ�ڷ�������)��Krֵ��
 */

RGBColor Transparent::shade(ShadeRec & sr)
{
	RGBColor L(Phong::shade(sr));

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);//computes wi
	Ray reflected_ray(sr.hit_point, wi);

	if (specular_brdf->tir(sr))
		L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
	    //kr=1.0
	else
	{
		Vector3D wt;
		RGBColor ft = specular_brdf->sample_f(sr, wo, wt);//computes wt
		Ray transmitted_ray(sr.hit_point, wt);

		L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)*fabs(sr.normal*wi);

		L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1)*fabs(sr.normal*wt);
	}
	//����Ϊ���⴦�����ע�͵���������ɫͼ�ߴ��󣬾����������Ϊ��ɫ�е�Rֵ��Ϊ�˸�ֵ
	if (L.r < 0) L.r = 0;
	if (L.g < 0) L.g = 0;
	if (L.b < 0) L.b = 0;
	return(L);
}