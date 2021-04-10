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

	virtual BBox get_bounding_box(void);//���������εİ�Χ��

public:
	Point3D v0, v1, v2;//�����ζ���
	Normal normal;
};

