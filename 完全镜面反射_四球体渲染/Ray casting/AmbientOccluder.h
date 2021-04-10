#pragma once

#include"Light.h"
#include"Sampler.h"

class AmbientOccluder:public Light
{
public:

	AmbientOccluder(void);

	~AmbientOccluder(void);

	void scale_radiance(const float b);

	void set_color(const RGBColor& color);

	void set_min_amount(const float amount);

	void set_sampler(Sampler* s_ptr);

	virtual Vector3D get_direction(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;

	virtual RGBColor L(ShadeRec& sr);

private:
	float ls;
	RGBColor color;
	Vector3D u, v, w;//����������
	Sampler* sampler_ptr;//������ָ��
	float min_amount;
};
/*
˵����
1.set_sampler()�����������ò���������sp����build()�����м��Թ��죩��������������ҷֲ�(e=1)�ķ�ʽ������ӳ��������ģ���ϡ�
2.get_direction()�������ظ�����Ӱ���ߵķ��򡣸ú���ֻ�Ǽ򵥵ؽ��ֲ���������ط���ͶӰ��(u,v,w)�ϡ�
3.in_shadow()��������Ӱ����-������ײ��⺯�������ڽ�һ��������Ӱ�����Ƿ�ĳһ�������赲��
4.L()������ʾ�������������Ĺ��������Լ�get_direction()��in_shadow()�����ĵ��÷�ʽ�����ǣ�����L()�ڵ���get_direction()֮ǰ����(u,v,w)������
���⣬�����߷����赲ʱ����ʹ�����ݳ�Աmin_amount�Է�����С����ɫֵ���Ǻ�ɫ�����뷵�غ�ɫֵ��ȣ���������ɫ�������ʵ�У�
�Ͼ�����ʵ���������еĸ������������ܲ�ͬ�̶ȵĹ��ա�
5.����Ĳ�����ʵ���ǽ���ǰ�Ļ�����̶���ɫ��Ϊ�˻�����ѡ������ɫ�������ȼ��������ռ�/���嶼���ܻ����⣬Ȼ��ȥ��ÿһ����ɫ��İ���ռ���
ѡ���������Ͷ����Ӱ���ߣ�����Ӱ���߷�����ײ������Ϊ�ò����㲻���ܻ��������䣬�����价������Ӱ��ɫ������Ӱ���߲�������ײ����Ϊ�ò�������ܻ��������䣬�����价������ɫ��
���ԣ�����������⣺�����ڵ��ǻ��������Ӱ����
*/

