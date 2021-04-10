#pragma once

#include"Vector3D.h"
class ShadeRec;
#include"RGBColor.h"
#include"Ray.h"

class Light
{
public:
	Light(void);

	virtual~Light(void);

	virtual Vector3D get_direction(ShadeRec& sr) = 0;

	virtual RGBColor L(ShadeRec& sr) = 0;

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const = 0;//碰撞点是否在阴影之中

	virtual bool casts_shadows();//是否开启阴影光线投射

	virtual float G(const ShadeRec& sr)const;

	virtual float pdf(ShadeRec& sr);

public:
	bool shadows;//阴影
};
/*
说明：
1.get_direction()函数返回碰撞点处的光线方向
2.L()函数返回碰撞点处的入射辐射度
3.关于ls和color并未出现在基类中的原因：针对区域光照以及环境光照，ls()函数位于对应光照所使用的发射材质中。
区域光照将包含纹理材料且颜色值依赖于位置的变化。
*/

