#pragma once

#include"GeometricObject.h"

class Torus:public GeometricObject
{
public:
	Torus(void);
	
	Torus(const double _a, const double _b);

	~Torus(void);

	Normal compute_normal(const Point3D& p)const;

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

private:
	double a;//ɨ�Ӱ뾶
	double b;//��״�뾶
	BBox bbox;//��Χ��
};

