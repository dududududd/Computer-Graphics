#include "pch.h"
#include "Box.h"

#include"World.h"

Box::Box(void)
	:GeometricObject(),
	x0(-1.0), y0(-1.0), z0(-1.0),
	x1(1.0), y1(1.0), z1(1.0)
{

}

Box::Box(const Point3D & p1, const Point3D & p2)
	:GeometricObject()
{
	this->x0 = p1.x;
	this->y0 = p1.y;
	this->z0 = p1.z;
	this->x1 = p2.x;
	this->y1 = p2.y;
	this->z1 = p2.z;
}

Box::Box(const double _x0, const double _x1, const double _y0, const double _y1, const double _z0, const double _z1)
	:GeometricObject(), x0(_x0), x1(_x1), y0(_y0), y1(_y1), z0(_z0), z1(_z1)
{

}

Box::~Box(void)
{
}

bool Box::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
	double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0)
	{
		tx_min = (x0 - ox)*a;
		tx_max = (x1 - ox)*a;
	}
	else
	{
		tx_min = (x1 - ox)*a;
		tx_max = (x0 - ox)*a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		ty_min = (y0 - oy)*b;
		ty_max = (y1 - oy)*b;
	}
	else
	{
		ty_min = (y1 - oy)*b;
		ty_max = (y0 - oy)*b;
	}
	double c = 1.0 / dz;
	if (c >= 0)
	{
		tz_min = (z0 - oz)*c;
		tz_max = (z1 - oz)*c;
	}
	else
	{
		tz_min = (z1 - oz)*c;
		tz_max = (z0 - oz)*c;
	}

	int face_in, face_out;

	float t0, t1;
	//找到最大的输入t值

	if (tx_min > ty_min)
	{
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0)
	{
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}

	//找到最小的退出t值

	if (tx_max < ty_max)
	{
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = ty_max;
		face_out = (a >= 0.0) ? 4 : 1;
	}
	if (tz_max < t1)
	{
		t1 = tz_max;
		face_out = (c >= 0.0) ? 5 : 2;
	}

	if (t0<t1&&t1>kEpsilon)//碰撞条件
	{
		if (t0 > kEpsilon)
		{
			tmin = t0;//射线击中外表面
			sr.normal = get_normal(face_in);
		}
		else
		{
			tmin = t1;//射线击中内表面
			sr.normal = get_normal(face_out);
		}

		sr.local_hit_point = ray.o + tmin * ray.d;
		return(true);
	}
	else
	{
		return(false);
	}
}

bool Box::shadow_hit(const Ray & ray, float & tmin) const
{
	double ox = ray.o.x; double oy = ray.o.y; double oz = ray.o.z;
	double dx = ray.d.x; double dy = ray.d.y; double dz = ray.d.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0)
	{
		tx_min = (x0 - ox)*a;
		tx_max = (x1 - ox)*a;
	}
	else
	{
		tx_min = (x1 - ox)*a;
		tx_max = (x0 - ox)*a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		ty_min = (y0 - oy)*b;
		ty_max = (y1 - oy)*b;
	}
	else
	{
		ty_min = (y1 - oy)*b;
		ty_max = (y0 - oy)*b;
	}
	double c = 1.0 / dz;
	if (c >= 0)
	{
		tz_min = (z0 - oz)*c;
		tz_max = (z1 - oz)*c;
	}
	else
	{
		tz_min = (z1 - oz)*c;
		tz_max = (z0 - oz)*c;
	}

	int face_in, face_out;

	float t0, t1;
	//找到最大的输入t值

	if (tx_min > ty_min)
	{
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0)
	{
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}

	//找到最小的退出t值

	if (tx_max < ty_max)
	{
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = ty_max;
		face_out = (a >= 0.0) ? 4 : 1;
	}
	if (tz_max < t1)
	{
		t1 = tz_max;
		face_out = (c >= 0.0) ? 5 : 2;
	}

	if (t0<t1&&t1>kEpsilon)//碰撞条件
	{
		if (t0 > kEpsilon)
		{
			tmin = t0;//射线击中外表面
		}
		else
		{
			tmin = t1;//射线击中内表面
		}

		return(true);
	}
	else
	{
		return(false);
	}
}

Normal Box::get_normal(const int face_hit) const
{
	switch (face_hit)
	{
		case 0:return(Normal(-1, 0, 0));//-x face
		case 1:return(Normal(0, -1, 0));//-y face
		case 2:return(Normal(0, 0, -1));//-z face
		case 3:return(Normal(1, 0, 0));//+x face
		case 4:return(Normal(0, 1, 0));//+y face
		case 5:return(Normal(0, 0, 1));//+z face
	}
}
