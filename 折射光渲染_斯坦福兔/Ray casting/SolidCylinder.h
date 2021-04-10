#pragma once

#include"Compound.h"

class SolidCylinder:public Compound
{
public:
	SolidCylinder(void);

	SolidCylinder(const SolidCylinder& cc);

	SolidCylinder(const float bottom, const float top, const float radius);

	~SolidCylinder(void);
	
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

public:
	BBox bbox;
};