#pragma once

#include"GeometricObject.h"

class Triangle:public GeometricObject
{
public:
	Triangle(void);

	Triangle(const Point3D& a, const Point3D& b, const Point3D& c);

	~Triangle(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

	virtual BBox get_bounding_box(void);//计算三角形的包围盒

public:
	Point3D v0, v1, v2;//三角形顶点
	Normal normal;
};

