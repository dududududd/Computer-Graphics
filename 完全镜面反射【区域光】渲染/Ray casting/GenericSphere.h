#pragma once

#include"GeometricObject.h"

class GenericSphere:public GeometricObject
{
public:
	GenericSphere(void);

	~GenericSphere(void);
	
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

};