#pragma once

#include"Light.h"

class PointLight:public Light
{
public:

	PointLight(void);

	~PointLight(void);

	void set_location(const double a, const double b, const double c);

	void set_color(const RGBColor& color);

	void scale_radiance(const float b);

	//void set_Attenuation_factor(const int P);//���õ��Դ����˥������

	virtual Vector3D get_direction(ShadeRec& sr);

	bool in_shadow(const Ray& ray, const ShadeRec& sr)const;//�ж���ɫ���Ƿ�����Ӱ������

	bool casts_shadows();//�Ƿ�����ӰͶ��

	virtual RGBColor L(ShadeRec& sr);

private:
	float ls;
	RGBColor color;
	Vector3D location;
	//int P;//����˥������
};
/*
˵����
1.get_direction()����������һ��������ײ��ĵ�λ�����������仹ʹ���˴洢��ShadeRec�����е���ײ�����ꡣ
2.�������ھ���˥����L()������ͬ��Ambient::L()������
*/

