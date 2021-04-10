#pragma once

#include"GeometricObject.h"

class OpenCylinder2 :public GeometricObject
{
public:
	OpenCylinder2(void);

	OpenCylinder2(const double _y0, const double _y1, const double _radius);

	~OpenCylinder2(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

private:

	double y0;
	double y1;
	double radius;
	double inv_radius;
	static const double kEpsilon;
	BBox bbox;
};