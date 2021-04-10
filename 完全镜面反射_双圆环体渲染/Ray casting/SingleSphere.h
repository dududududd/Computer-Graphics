#pragma once

#include"Tracer.h"

class SingleSphere:public Tracer
{
public:
	SingleSphere(void);//默认构造函数
	SingleSphere(World* _worldPtr);//构造函数
	
	~SingleSphere(void);//析构函数
	//virtual RGBColor trace_ray(const Ray& ray)const;//光线跟踪器函数
};
/*
说明：
1.该类继承自基类Tracer类，其中没有新增的数据成员。
2.子类构造函数需要对基类数据成员进行初始化。
*/

