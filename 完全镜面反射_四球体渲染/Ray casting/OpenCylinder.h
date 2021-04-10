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
说明：
1.关于这里要反向点法矢量的原因：
因为这个几何体是空心的，也就是说其内部是可以看到的，所以其内部点也可能需要着色计算，
而这时再使用外部表面的法矢量显然是不合适的，所以，如果是内表面需要将法矢量反向。
同样的，我们还可以上升到普通物体层面上，所有需要双面着色的物体都需要进行法矢量反向。
*/