#include "pch.h"
#include "RoundrimSolidBowl.h"

#include"Torus.h"
#include"PartSphere.h"
#include"Constants.h"

#include"Instance.h"

RoundrimSolidBowl::RoundrimSolidBowl(void)
	:Compound(), bbox(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)
{

}

RoundrimSolidBowl::RoundrimSolidBowl(const double radius, const double Radius, const double theta_min)
	:Compound()
{
	double a = (0.5*(radius + Radius))*sin(theta_min*PI_ON_180);
	double b = 0.5*(Radius - radius);
	double Y_translate = (0.5*(radius + Radius))*cos(theta_min*PI_ON_180);

	//内球体
	objects.push_back(new PartSphere(Point3D(0.0), radius, 0.0, 360.0, theta_min, 180.0));
	
	//外球体
	objects.push_back(new PartSphere(Point3D(0.0), Radius, 0.0, 360.0, theta_min, 180.0));
	
	//圆滑边缘
	Instance* torus_ptr = new Instance(new Torus(a, b));
	torus_ptr->translate(0.0, Y_translate, 0.0);
	objects.push_back(torus_ptr);

	//构造包围盒
	bbox.x0 = -Radius; bbox.x1 = Radius;
	bbox.y0 = -Radius; bbox.y1 = Y_translate + b;
	bbox.z0 = -Radius; bbox.z1 = Radius;
}

RoundrimSolidBowl::~RoundrimSolidBowl(void)
{
}

bool RoundrimSolidBowl::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	if (bbox.hit(ray))
		return(Compound::hit(ray, tmin, sr));
	else
	{
		return(false);
	}
}

bool RoundrimSolidBowl::shadow_hit(const Ray & ray, float & tmin) const
{
	if (bbox.hit(ray))
	{
		return(Compound::shadow_hit(ray, tmin));
	}
	else
	{
		return(false);
	}
}