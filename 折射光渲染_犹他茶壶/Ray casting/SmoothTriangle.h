#pragma once

#include"GeometricObject.h"

class SmoothTriangle:public GeometricObject
{
public:

	SmoothTriangle(void);

	SmoothTriangle(const Point3D& a, const Point3D& b, const Point3D& c);

	SmoothTriangle(const SmoothTriangle& st);

	SmoothTriangle& operator= (const SmoothTriangle& rhs);

	virtual~SmoothTriangle(void);

	virtual BBox get_bounding_box(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

public:
	Normal n0, n1, n2;//每个顶点的法线
	Point3D v0, v1, v2;
	Normal interpolate_normal(const float beta, const float gamma) const;
};

/*
此三角形有三条法线，它们在平滑着色的命中点处进行线性插值
使法线公开可简化Grid:：tessellate_smooth_sphere中的代码。
*/