#pragma once

#include"GeometricObject.h"
#include<vector>

class Compound:public GeometricObject
{
public:

	Compound(void);

	virtual ~Compound(void);

	virtual void set_material(Material* material_ptr);

	virtual void add_object(GeometricObject* object_ptr);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

	int get_num_objects(void);

	void delete_objects(void);

protected:

	std::vector<GeometricObject*>objects;
};

