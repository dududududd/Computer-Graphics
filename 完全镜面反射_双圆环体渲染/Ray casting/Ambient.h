#pragma once

#include"Light.h"
#include"RGBColor.h"

class Ambient:public Light
{
public:

	Ambient(void);

	~Ambient(void);

	void scale_radiance(const float b);

	void set_color(const RGBColor& color);

	virtual Vector3D get_direction(ShadeRec& sr);

	virtual RGBColor L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;//��ײ���Ƿ�����Ӱ֮��

private:
	float ls;
	RGBColor color;
};
/*
˵����
1.�������յ��������ȿɱ�ʾΪ��Li=ls*cl�����У�lsΪ����ϵ����clΪ��ɫֵ�����ｫ�����⵱��һ����ֵ������
2.���价�������ΪL0=��hh*Li��
3.Ambient�ಢ���漰���������⡣
4.L()����������ls*cl
5.get_direction()���������������ù���������صļ��㣬ֻ�Ǽ򵥵ط���0������
*/
