#pragma once//预编译指令，避免同名冲突

#include"Point3D.h"
#include"Vector3D.h"

class Ray
{	
public:
	Ray(void);//默认构造函数
	Ray(const Point3D& origin, const Vector3D& dir);//构造函数
	Ray(const Ray& ray);//拷贝构造函数

	Ray& operator=(const Ray& rhs);//赋值运算符重载
	~Ray(void);//析构函数
public:
	Point3D o;//光源点
	Vector3D d;//方向向量
};
/*
说明：
1.在该类中，【拷贝构造函数】和【赋值运算符重载】是可以省略的，因为数据成员中没有指针变量，浅拷贝不会造成指针悬挂。
2.该类不作为基类，【析构函数】前不加virtual为最优方案。当声明为虚析构时会增加虚函数表，增加内存占用。
3.为了便于对该类数据成员的访问，选择将其访问属性设置为公有。
4.【构造函数】，形参引用前面加const指该函数只参与外部传入数据的读取不参与修改。
*/