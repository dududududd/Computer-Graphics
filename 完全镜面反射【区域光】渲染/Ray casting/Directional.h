#pragma once

#include"Light.h"

class Directional:public Light
{
public:
	Directional(void);

	~Directional(void);

	void scale_radiance(const float b);

	void set_color(const RGBColor& color);

	void set_direction(const Vector3D& v);

	virtual Vector3D get_direction(ShadeRec& sr);

	virtual RGBColor L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;

	bool casts_shadows();

private:

	float ls;
	RGBColor color;
	Vector3D dir;
};