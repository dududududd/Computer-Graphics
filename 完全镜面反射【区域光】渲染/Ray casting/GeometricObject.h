#pragma once

#include"Ray.h"
class ShadeRec;
class Material;
#include"Normal.h"

#include"BBox.h"

class GeometricObject
{
public:
	GeometricObject(void);//默认构造函数

	GeometricObject(const GeometricObject& object);//拷贝构造函数
	
	GeometricObject& operator=(const GeometricObject& geometricobject);//赋值运算符重载
	
	virtual~GeometricObject(void);//虚析构函数
	
	//RGBColor get_color(void);
	
	Material* get_material(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const = 0;//光线-对象相交测试函数(纯虚函数)
	
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;//阴影光线-对象相交测试函数
	
	virtual Point3D sample(void);

	virtual float pdf(ShadeRec& sr);

	virtual Normal get_normal(const Point3D& p);

	virtual Normal get_normal(void) const;

	virtual void set_material(Material* material_ptr);

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

	virtual void add_object(GeometricObject* object_ptr);

public:
	//RGBColor color;//颜色字段
	mutable Material* material;//材质指针
	bool shadows;//用于设置对象阴影选项
};
/*
说明：
1.在该类中，【拷贝构造函数】和【赋值运算符重载】是可以省略的，因为数据成员中没有指针变量，浅拷贝不会造成指针悬挂。
2.该类作为几何对象的基类，析构函数必须设置为虚析构函数，因为当基类析构函数被调用时，基类指针会指向派生类并调用其析构函数并释放全部内存；非虚析构函数时只会调用基类的析构函数造成内存释放不完全。
3.关于数据成员，目前并不涉及光照的计算，所以采用RGBColor字段来代替。
4.因为是继承结构，所以将数据成员的访问属性设置为保护。
5.该类为抽象类，无需对光线-对象相交测试函数进行实现。
*/