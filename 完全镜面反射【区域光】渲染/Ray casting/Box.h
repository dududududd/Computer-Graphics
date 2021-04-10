#pragma once

#include"GeometricObject.h"

class Box:public GeometricObject
{
public:
	Box(void);

	Box(const Point3D& p1, const Point3D& p2);

	Box(const double _x0, const double _x1, const double _y0, const double _y1, const double _z0, const double _z1);

	~Box(void);

	bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

	Normal get_normal(const int face_hit)const;//计算轴对齐盒体的法矢量

private:
	double x0, y0, z0;
	double x1, y1, z1;
};