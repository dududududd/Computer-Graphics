#pragma once

#include"BRDF.h"

class GlossySpecular:public BRDF
{
public:

	GlossySpecular(void);

	~GlossySpecular(void);

	void set_ks(const float ks);

	void set_exp(const float exp);

	void set_cs(const RGBColor& cs);//������ɫ�߹�

	void set_sampler(Sampler* sp, const float exp);//�κ����͵Ĳ���

	void set_samples(const int num_smaples, const float exp);//���ض�������

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

private:
	float ks;//���淴��ϵ��
	RGBColor cs;//������ɫֵ
	float exp;//��e
};