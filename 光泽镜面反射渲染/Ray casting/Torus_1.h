#pragma once

#include"GeometricObject.h"

class Torus_1 :public GeometricObject
{
public:
	Torus_1(void);

	Torus_1(const Point3D& _p, const double _r1, const double _r2, Normal& _normal);

	~Torus_1(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

private:
	Point3D center;
	double radius1;//�ڰ뾶
	double radius2;//��뾶
	Normal normal;
};