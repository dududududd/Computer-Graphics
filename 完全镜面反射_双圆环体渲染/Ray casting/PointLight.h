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

	//void set_Attenuation_factor(const int P);//设置点光源距离衰减因子

	virtual Vector3D get_direction(ShadeRec& sr);

	bool in_shadow(const Ray& ray, const ShadeRec& sr)const;//判断着色点是否在阴影光线上

	bool casts_shadows();//是否开启阴影投射

	virtual RGBColor L(ShadeRec& sr);

private:
	float ls;
	RGBColor color;
	Vector3D location;
	//int P;//距离衰减因子
};
/*
说明：
1.get_direction()函数将返回一个背向碰撞点的单位向量。并且其还使用了存储于ShadeRec对象中的碰撞点坐标。
2.若不存在距离衰减，L()函数等同于Ambient::L()函数。
*/

