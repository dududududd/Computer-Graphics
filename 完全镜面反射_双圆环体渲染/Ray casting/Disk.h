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
˵����
1.����ȷ��Բ�ϵ�һ��������ķ�����center+radius*�����������꣩������������Ҫ���ǵ�ȷ��һ����Բ�ĵ�ƽ����У�
��Բ�ĵ�ƽ������������ֱ�Ӽ��������ʱ���ܸõ㲢����Բ�ϣ��⽫�Ǵ���ģ�������Ҫ��Բ��Ϊ���㹹��uvw����������ϵ��
Ȼ���ټ���������������ܱ�֤������һ����Բ�ϡ�
*/