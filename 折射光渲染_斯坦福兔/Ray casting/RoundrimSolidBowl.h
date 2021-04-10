#pragma once
#include"Compound.h"

class RoundrimSolidBowl :public Compound
{
public:
	RoundrimSolidBowl(void);

	RoundrimSolidBowl(const double radius, const double Radius, const double theta_min);

	~RoundrimSolidBowl(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float & tmin)const;

private:
	BBox bbox;
};