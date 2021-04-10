#pragma once

#include"GeometricObject.h"

class OpenCylinder:public GeometricObject
{
public:
	OpenCylinder(void);

	OpenCylinder(const double _y0, const double _y1, const double _radius);

	~OpenCylinder(void);

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
/*
˵����
1.��������Ҫ����㷨ʸ����ԭ��
��Ϊ����������ǿ��ĵģ�Ҳ����˵���ڲ��ǿ��Կ����ģ��������ڲ���Ҳ������Ҫ��ɫ���㣬
����ʱ��ʹ���ⲿ����ķ�ʸ����Ȼ�ǲ����ʵģ����ԣ�������ڱ�����Ҫ����ʸ������
ͬ���ģ����ǻ�������������ͨ��������ϣ�������Ҫ˫����ɫ�����嶼��Ҫ���з�ʸ������
*/