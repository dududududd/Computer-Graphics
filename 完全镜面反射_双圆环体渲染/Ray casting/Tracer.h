#pragma once

#include"Ray.h"
#include"RGBColor.h"

class World;

class Tracer
{
public:
	Tracer(void);//默认构造函数

	Tracer(World* _world_ptr);//构造函数

	Tracer(const Tracer& tracer);//拷贝构造函数

	Tracer& operator=(const Tracer& tracer);//赋值运算符重载

	virtual~Tracer(void);//虚析构函数

	virtual RGBColor trace_ray(const Ray& ray)const;//光线跟踪器函数
	
	virtual RGBColor trace_ray(const Ray ray, const int depth)const;

	virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth)const;

protected:
	World* world_ptr;//World指针，用于访问场景中的几何对象和背景颜色
};
/*
说明：
1.该类作为基类，其析构函数应该声明为虚析构函数
2.因为数据成员中有指针变量，所以需要写【拷贝构造函数】和【赋值运算符重载】。
3.因为该类作为基类，数据成员的访问属性写成保护。
4.包含tmin参数的trace_ray()函数仅用于实现基于Dielectric材质的颜色过滤计算。
5.depth参数用于模拟反射以及透明度。
*/
