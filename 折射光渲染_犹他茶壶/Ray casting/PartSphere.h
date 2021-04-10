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

	Point3D center;//球体中心
	double radius;//球体半径
	double phi_min;//从+ve z轴逆时针测量的最小方位角（度）
	double phi_max;//从+ve z轴逆时针测量的最大方位角（度）
	double theta_min;//从+ve y轴向下测量的最小极角（以度为单位）
	double theta_max;//从+ve y轴向下测量的最大极角（度）
	double cos_theta_min;//存储以避免重复计算
	double cos_theta_max;//存储以避免重复计算
	static const double kEpsilon;
};

