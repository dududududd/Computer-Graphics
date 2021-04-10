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
	Vector3D u, v, w;//正交基向量
	Sampler* sampler_ptr;//采样器指针
	float min_amount;
};
/*
说明：
1.set_sampler()函数用于设置采样器对象sp（在build()函数中加以构造），并于随后以余弦分布(e=1)的方式将采样映射至半球模型上。
2.get_direction()函数返回各条阴影光线的方向。该函数只是简单地将局部变量的相关分量投影至(u,v,w)上。
3.in_shadow()采样点阴影光线-对象碰撞检测函数，用于进一步测试阴影光线是否被某一对象所阻挡。
4.L()函数显示了正交基向量的构建过程以及get_direction()和in_shadow()函数的调用方式。但是，函数L()在调用get_direction()之前即对(u,v,w)构建。
另外，当光线方向被阻挡时，可使用数据成员min_amount以返回最小的颜色值（非黑色）。与返回黑色值相比，增加了着色结果的真实感，
毕竟，真实场景世界中的各个表面均会接受不同程度的光照。
5.这里的操作其实就是将以前的环境光固定着色变为了环境光选择性着色：我们先假设整个空间/物体都接受环境光，然后去在每一个着色点的半球空间上
选择采样点来投射阴影光线，当阴影光线发生碰撞，则认为该采样点不接受环境光照射，给予其环境光阴影着色；当阴影光线不发生碰撞，认为该采样点接受环境光照射，给予其环境光着色。
所以，可以这样理解：环境遮挡是环境光的阴影处理。
*/

