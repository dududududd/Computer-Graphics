#pragma once

#include"GeometricObject.h"
#include"Sampler.h"

class CRectangle:public GeometricObject
{
public:

	CRectangle(void);

	~CRectangle(void);

	CRectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);

	CRectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& _n);

	virtual void set_sampler(Sampler* sampler);//设置采样器指针

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;//光线-对象相交测试函数

	virtual Point3D sample(void);//将单位正方形上的采样点映射到矩形上

	virtual float pdf(ShadeRec& sr);//获得矩形上的采样点概率密度函数，这里假设为获得各采样点的概率相同

	virtual Normal get_normal(const Point3D& p);//获得矩形的法矢量（矩形上的点的法矢量都是相同的且已经在矩形定义时设置）

	void set_material(Material* material_ptr);//设置对象材质

	virtual BBox get_bounding_box(void);

private:

	Point3D p0;//获取的单位正方形上的采样点
	Vector3D a;//矩形边向量(不为单位向量)
	Vector3D b;//矩形边向量(不为单位向量)
	double a_len_squared;//边长a的平方
	double b_len_squared;//边长b的平方
	Normal normal;//采样点的法矢量
	Sampler* sampler_ptr;//采样器指针
	float inv_area;//表面积的倒数
	static const double kEpsilon;//一个极小值
};