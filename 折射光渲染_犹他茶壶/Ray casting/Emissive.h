#pragma once

#include"Material.h"

//自发光材质
class Emissive:public Material
{
public:
	Emissive(void);

	~Emissive(void);

	void scale_radiance(const float _ls);//设置辐射范围

	void set_ce(const float r, const float g, const float b);//设置辐射颜色

	virtual RGBColor get_Le(ShadeRec& sr)const;//获得辐射光

	virtual RGBColor shade(ShadeRec& sr);//绘制

	virtual RGBColor area_light_shade(ShadeRec& sr);//面积光绘制

	virtual RGBColor path_shade(ShadeRec& sr);

private:
	float ls;//辐射比例因子(缩放系数)
	RGBColor ce;//自发光颜色值
};
/*
说明：
1.shade()函数使得自发光材质可与其他类型的光线跟踪器结合使用。另外，仅当
入射光线与对象表面法线位于同一侧时，两个函数均返回Le=lsCe；否则函数将返回黑色值。
此处，常量自发光颜色值以及同性发射方式最终将使自发光对象呈现为固定着色状态。
*/
/*
说明：对于自发光对象我们考虑其具有两种属性：
1.对象属性：其需要被相机看到，能够反射光（这里我们为了简化并未考虑反射，所以从对象角度来说其不能被相机看到）
2.光源属性：能够辐射光，当从光源角度来看时，其能发射光进入相机，所以其能够被相机看到。
*/
/*
注意：自发光材质的发射辐射度与位置和方向是有关的，但是这里为了简化，假设与位置和方向无关。
*/

