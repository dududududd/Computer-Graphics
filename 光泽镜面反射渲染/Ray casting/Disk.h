#pragma once

#include"GeometricObject.h"
#include"Sampler.h"

class Disk:public GeometricObject
{
public:

	Disk(void);

	~Disk(void);

	Disk(const Point3D& _center, const double _radius, const Normal& _n);

	virtual void set_sampler(Sampler* sampler);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual Point3D sample(void);

	virtual float pdf(ShadeRec& sr);

	virtual Normal get_normal(const Point3D& p);

	void set_material(Material* material_ptr);

	void compute_uvw(void);

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

private:
	Point3D center;
	Vector3D u, v, w;
	float radius;
	Normal normal;
	Sampler* sampler_ptr;
	float inv_area;
	static const double kEpsilon;
	BBox bbox;
};
/*
说明：
1.对于确定圆上的一个采样点的方法是center+radius*（采样点坐标），但是这里需要考虑得确定一个过圆心的平面才行，
过圆心的平面有无数个，直接计算采样点时可能该点并不在圆上，这将是错误的，所以需要以圆心为基点构建uvw基向量坐标系，
然后再计算采样点的坐标才能保证采样点一定在圆上。
*/