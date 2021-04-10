#pragma once

#include<vector>//vector容器
#include"ViewPlane.h"
#include"Sphere.h"
#include"Plane.h"
#include"GeometricObject.h"
#include"Whitted.h"
#include"Maths.h"

class Light;
#include"Camera.h"
class PinHole;

#include"Instance.h"
//#include"Grid.h"
//#include"CBezierPatch.h"
#include"CTeapot.h"
#include"Box.h"
#include"SolidCylinder.h"
#include"CRectangle.h"

#include"Directional.h"
#include"PointLight.h"
#include"AmbientOccluder.h"
#include"AreaLighting.h"
#include"EnvironmentLight.h"
#include"Emissive.h"
#include"AreaLight.h"
#include"PointLight.h"

#include"Matte.h"
#include"Phong.h"
#include"GlossyReflector.h"
#include"Reflective.h"

class World
{
public:
	World(void);//默认构造函数
	~World(void);//析构函数

	World(const World& _world);//拷贝构造函数
	World& operator=(const World& _world);//赋值运算符重载

	void build(void);//设置相关参数

	void add_object(GeometricObject* object_ptr);//添加渲染对象

	void add_light(Light* light_ptr);

	RGBColor max_to_one(const RGBColor& c)const;//溢色处理方法1

	RGBColor clamp_to_color(const RGBColor& raw_color)const;//溢色处理方法2

	ShadeRec hit_objects(const Ray& ray);//获取最近碰撞点的属性

	//void render_scene(void)const;//视平面投射光线渲染场景

	//void render_perspective(void)const;//用于计算一条光线穿越像素中心位置时的轴对齐透视图

	void open_window(const int hres, const int vres)const;//开启渲染窗口

	void display_pixel(const int row, const int column,RGBColor& raw_color)const;//绘制像素

public:
	ViewPlane vp;//视平面
	RGBColor background_color;//背景颜色
	Tracer* tracer_ptr;//跟踪类指针
	std::vector<GeometricObject*>objects;//新增内容
	CDC* pDC;//MFC类库绘图指针 
	static const double kHugeValue;//假设为无穷大值
	//double eye;//视见点
	//double d;//视平面距离
	Camera* camera_ptr;//相机指针
	Light* ambient_ptr;
	std::vector<Light*>lights;
};
/*
说明：
1.关于open_window(hres,vres)函数，其作用是开启一个渲染窗口，但是由于本程序采用的是MFC类库，并没有使用到该函数来创建窗口
2.关于整个多对象的光线投射器的渲染流程：我主要说明类的作用；
①ShadeRec类是用来存储计算所需的属性值的。
②几何对象类是用来存储几何物体的绘制信息和光线-对象相交测试函数的。
③跟踪器类是用来计算经其他类传递过来的对象的材质光照的。
④World类是调用其他函数的类，其将调用其他函数实现一个整体的跟踪器，相当于main()函数。
3.代码未定义特点的几何对象类型，因而适用于几何对象继承层次结构中的任意对象类型，并实现了基于hit()函数的公共接口。
4.轴对齐投影利用render_perspective()实现，并在主函数中调用以替换原render_scene()函数。
5.ambient_ptr环境光照指针采用了Light指针而非Ambient指针，以适应各种Ambient类型的赋值操作。
6.在World类的默认构造函数中，Ambient指针将初始化为指向某一Ambient对象而非空指针。鉴于需要针对各材质独立设置ka参数，
该Ambient对象将应用于多数场景中。最终结果为：当需要定义ls时或改变默认颜色时，可在build()函数中设置Ambient光照。
*/