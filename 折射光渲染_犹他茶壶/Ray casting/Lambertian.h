#pragma once

#include"BRDF.h"

class Lambertian:public BRDF//��ȫ������
{
public:

	Lambertian(void);

	~Lambertian(void);

	void set_kd(const float kd);

	void set_cd(const RGBColor& cd);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo)const;
	
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;
	
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const;

private:
	float kd;//������ϵ��
	RGBColor cd;//��������ɫֵ
};
/*
˵����
1.��d�ɱ�ʾΪRGB��ɫֵ����ɱ�ʾΪ��d=kd*cd;kd��ʾ������ϵ����cd��ʾΪ��������ɫֵ��
��BRDF�ɱ�ʾΪf(r,d)=kd*cd/����
2.�������kd��cd�˻�����ʽ��ʾ��d��ԭ���Ǳ����û������ݵ��޸ġ�
3.��d�����������ǣ���BRDF������Ǻͳ�����޹�ʱ�����������������ƬdA�Ϸ�ȫ�������ڲ��ķ���ͨ����ȫ������ͨ��֮�ȡ�
4.�ʲ������嶨��Ϊ��ȫ������
5.������ȫ������Ļ�������ģ�Ͷ��ԣ�ͨ������˫������ϵ����hh��ʾ�����������Ⱦ���ͬ�����Լ��ռ䲻����ʱ���÷�����ʾ
ȫ�����ڵķ���ͨ����ȫ������ͨ��֮�ȡ�
*/
/*
˵����
1.���ԣ�����������Ҫ����ģ�⻷����������ġ�
*/