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

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;//碰撞点是否在阴影之中

private:
	float ls;
	RGBColor color;
};
/*
说明：
1.环境光照的入射辐射度可表示为：Li=ls*cl，其中，ls为缩放系数，cl为颜色值。这里将环境光当做一个定值来处理。
2.反射环境辐射度为L0=Ρhh*Li。
3.Ambient类并不涉及方向性问题。
4.L()函数仅返回ls*cl
5.get_direction()函数将不会参与与该光照类型相关的计算，只是简单地返回0向量。
*/
