#pragma once

#include"GeometricObject.h"

class PartSphere:public GeometricObject
{
public:
	PartSphere(void);

	PartSphere(const Point3D _center, const double _radius);

	PartSphere(const Point3D _center, const double _radius, const double _phi_min, const double _phi_max, const double _theta_min, const double _theta_max);

	~PartSphere(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

public:

	Point3D center;//��������
	double radius;//����뾶
	double phi_min;//��+ve z����ʱ���������С��λ�ǣ��ȣ�
	double phi_max;//��+ve z����ʱ����������λ�ǣ��ȣ�
	double theta_min;//��+ve y�����²�������С���ǣ��Զ�Ϊ��λ��
	double theta_max;//��+ve y�����²�������󼫽ǣ��ȣ�
	double cos_theta_min;//�洢�Ա����ظ�����
	double cos_theta_max;//�洢�Ա����ظ�����
	static const double kEpsilon;
};

