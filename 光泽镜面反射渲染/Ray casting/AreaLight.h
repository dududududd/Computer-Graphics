#pragma once

#include"Light.h"
#include"GeometricObject.h"
#include"Normal.h"

class AreaLight:public Light
{
public:
	AreaLight(void);

	~AreaLight(void);

	void set_object(GeometricObject* _object_ptr);//设置具有自发光属性的几何对象

	virtual Vector3D get_direction(ShadeRec& sr);//获得wi方向

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;//判断阴影光线碰撞
	
	virtual RGBColor L(ShadeRec& sr);//获得反射辐射度

	virtual float G(const ShadeRec& sr)const;//用于计算G(p.p')

	virtual float pdf(ShadeRec& sr);//概率密度函数

	virtual bool casts_shadows();//是否开启阴影

private:
	
	GeometricObject* object_ptr;//对象指针
	Material* material_ptr;//发光材质指针
	Point3D sample_point;//表面取样点
	Normal light_normal;//采样点上的法线
	Vector3D wi;//从碰撞点到采样点的单位向量
};
/*
说明：
1.get_direction()函数不仅返回着色点与采样点之间的单位方向向量wi,还将存储采样点、采样点处的法线以及wi至成员变量中，
因为in_shadow()、L()和G()同样需要这些数据。几何对象的get_normal()函数将被get_direction()函数调用，该函数只适用于平面对象以及某一
隐式函数所定义的对象，并不包括轴对齐盒体等这一类对象。
2.in_shadow()函数检测阴影光线是否与碰撞点和采样点之间的对象产生碰撞。
3.L()函数在返回材质的发射辐射度之前将检测光线是否位于法线同一侧的表面产生碰撞。
4.G()函数则计算余弦项cosθ'=-n'j*Wi,j并除以d²。这里，该结果值并非几何因子G(p,p'j)的全部内容，
另一个余弦因子n*Wi,j则在Matte::area_light_shade()函数中单独计算。
5.pdf()函数只是简单地调用当前对象的pdf()函数。
*/

