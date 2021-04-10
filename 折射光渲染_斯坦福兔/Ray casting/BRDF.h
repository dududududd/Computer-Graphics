#pragma once

#include"RGBColor.h"
#include"Vector3D.h"
class ShadeRec;
class Sampler;

class BRDF
{
public:
	BRDF(void);

	BRDF(const BRDF& brdf);

	BRDF& operator=(const BRDF& brdf);

	virtual~BRDF(void);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const = 0;//���㷢���ķ���

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const;

	virtual void set_sampler(Sampler* _sampler_ptr);

protected:

	Sampler* sampler_ptr;
};
/*
˵����
1.�������f()������delta������������BRDF����
2.����ڷ�������Լ�������-���������ģ����㣬����sample_f()���ڼ��㷴����ߵķ��򡣵��ǣ���Ҫע����ǣ�
����sample_f�����еĲ�����i���ڷ������յķ����������Ϊ����������ط���ͨ����BRDF��������õ�����Ҳ��BRDF�������һ������������ָ���ԭ��
3.����rho()������˫������ϵ����hh�����У�˫������ϵ��ָ������������䣺����������ڰ��򣬷����ͬ���ǰ���
*/
/*
1.f()�������ڼ���BRDF
2.ͨ���������Ա�ʾ�������ķ��������ǹ��߸��ټ����е�һ�ֳ������㷽����
*/