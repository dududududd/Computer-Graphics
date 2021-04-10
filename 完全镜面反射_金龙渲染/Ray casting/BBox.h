#pragma once

#include"Ray.h"

class BBox
{
public:
	BBox(void);

	BBox(const double _x0, const double _x1, const double _y0, const double _y1, const double _z0, const double _z1);

	~BBox(void);

	bool hit(const Ray& ray)const;

	bool inside(const Point3D& p)const;

public:
	double x0, y0, z0;
	double x1, y1, z1;
	static const double kEpsilon;
};