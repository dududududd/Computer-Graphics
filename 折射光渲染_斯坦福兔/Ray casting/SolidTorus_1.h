#pragma once

#include"Compound.h"

class SolidTorus_1 :public Compound
{
public:
	SolidTorus_1(void);

	SolidTorus_1(const float bottom, const float top, const float Radius, const float radius);

	~SolidTorus_1(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

	void set_outer_wall_material(Material* material_ptr);

	void set_inner_wall_material(Material* material_ptr);

	void set_top_material(Material* material_ptr);

	void set_bottom_material(Material* material_ptr);

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

private:
	BBox bbox;
};
