#pragma once

#include"Normal.h"
#include"GeometricObject.h"

class Plane:public GeometricObject
{
public:
	Plane(void);//默认构造函数
	
	Plane(const Point3D& p, Normal& n);//构造函数
	~Plane(void);//析构函数

	/*void set_color(const RGBColor& color);*/
	void set_material(Material* material);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;//光线-对象相交测试函数

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;//阴影光线-对象相交测试函数
public:
	Point3D point;//平面穿过的点
	Normal normal;//平面的法矢量
	static const double kEpsilon;//数值较小的一个正数
};
/*
说明：
1.关于【构造函数】的n采用Normal引用，而非const Normal引用：因为在构造函数中需要对其单位化时需要改变n的值大小。
2.因为该类中并没有纯虚函数，所以该类并不是抽象类。
3.kEpsilon是一个很小的值，但是不能为0，否则会出现某些问题。
4.该类是GeometricObject类的派生类，在构造函数中也需要对其基类数据成员进行初始化。
*/

