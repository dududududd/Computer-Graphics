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
	Normal n0, n1, n2;//ÿ������ķ���
	Point3D v0, v1, v2;
	Normal interpolate_normal(const float beta, const float gamma) const;
};

/*
�����������������ߣ�������ƽ����ɫ�����е㴦�������Բ�ֵ
ʹ���߹����ɼ�Grid:��tessellate_smooth_sphere�еĴ��롣
*/