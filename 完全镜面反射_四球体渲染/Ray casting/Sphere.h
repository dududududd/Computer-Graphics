#pragma once

#include"GeometricObject.h"
#include"ShadeRec.h"
#include"Sampler.h"

class Sphere:public GeometricObject
{
public:
	Sphere(void);//默认构造函数
	
	Sphere(const Point3D& _center, const double _radius);//构造函数
	
	~Sphere(void);//析构函数

	void set_sampler(Sampler* _sampler);

	virtual Point3D sample(void);

	virtual float pdf(ShadeRec& sr);

	virtual Normal get_normal(const Point3D& p);

	void set_center(const Point3D& p);//设置球体中心
	
	void set_radius(const double r);//设置球体半径
	//void set_color(const RGBColor& color);//设置球体颜色
	
	void set_material(Material* material);//设置球体材质

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;//光线-对象相交测试函数
	
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;//阴影光线-对象相交测试函数

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

public:
	double radius;//球体半径
	Point3D center;//球体中心
	Normal normal;
	Sampler* sampler_ptr;
	float inv_area;
	BBox bbox;//包围盒
	static const double kEpsilon;
};
/*
说明：
1.该类为GeometricObject类的派生类，需要对基类数据成员进行初始化。
2.在光线-对象相交测试函数中法矢量的计算在目前并没有起到作用。
*/