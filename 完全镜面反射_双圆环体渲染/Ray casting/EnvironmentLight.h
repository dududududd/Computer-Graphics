#pragma once

#include"Light.h"
#include"Sampler.h"
#include"Material.h"

class EnvironmentLight :public Light
{
public:

	EnvironmentLight(void);

	~EnvironmentLight(void);

	void set_sampler(Sampler* sampler);

	void set_material(Material* material);

	virtual Vector3D get_direction(ShadeRec& sr);

	virtual RGBColor L(ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;

	virtual float pdf(ShadeRec& sr);

public:
	Point3D sample_point;
	Sampler* sampler_ptr;
	Material* material_ptr;
	Vector3D u, v, w;
	Vector3D wi;
};