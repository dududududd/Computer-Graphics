#pragma once

#include"Normal.h"
#include"RGBColor.h"

#include"Ray.h"
#include"Material.h"
class World;

class ShadeRec
{
public:
	ShadeRec(World& wr);//构造函数，消除ShadeRec类的默认构造函数
	
	ShadeRec(const ShadeRec& sr);//拷贝构造函数
	~ShadeRec(void);//析构函数
	
	ShadeRec& operator=(const ShadeRec& rhs);//赋值运算符重载
public:
	bool hit_an_object;//光线是否与对象发生碰撞
	Material* material_ptr;//最近对象的材质
	Point3D hit_point;//命中点的世界坐标
	Point3D local_hit_point;//用于将纹理附加到对象
	Normal normal;//碰撞点的法矢量
	RGBColor color;//颜色
	Ray ray;//对于镜面高光
	int depth;//递归深度
	Vector3D dir;//对于区域光照
	double t;//矢量参数

	World& w;//World的引用
};
/*
说明：
1.该类是作为一个工具类，用来存储光线跟踪器所需的全部信息。
2.这里的【拷贝构造函数】和【赋值运算符重载】不是必须的。
3.ShadeRec(World& wr)存在的价值：使用其消除ShadeRec自带的默认构造函数是因为【引用】不能为空，而且ShadeRec作为一个中间类，是需要使用指针来进数值的传递的。
*/