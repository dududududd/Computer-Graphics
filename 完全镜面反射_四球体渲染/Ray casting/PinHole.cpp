#include "pch.h"
#include "PinHole.h"


PinHole::PinHole(void)
	:Camera(), d(500.0), zoom(1.0)
{

}

PinHole::~PinHole(void)
{

}

Vector3D PinHole::ray_direction(const Point2D& p)const
{
	Vector3D dir = p.x*u + p.y*v - d * w;//���ص������Դ�������ϵ�µĵķ�������
	dir.Normalize();
	return(dir);
}

void PinHole::render_scene(World& w)
{
	RGBColor L;
	ViewPlane vp(w.vp);
	Ray ray;
	int depth = 0; //�ݹ����
	Point2D sp;//��������[0,1]*[0,1]
	Point2D pp;//�����ϵĲ�����

	w.open_window(vp.hres, vp.vres);
	vp.s /= zoom;
	ray.o = eye;

	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++)
		{
			L = RGBColor(0.0);

			for (int j = 0; j < vp.num_samples; j++)
			{
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s*(c - 0.5*vp.hres + sp.x);
				pp.y = vp.s*(r - 0.5*vp.vres + sp.y);
				ray.d = ray_direction(pp);
				L += w.tracer_ptr->trace_ray(ray, depth);
			}

			L /= vp.num_samples; 
			L *= exposure_time;
			w.display_pixel(c, vp.vres - r, L);
		}
	}
}

void PinHole::set_d(const float dir)
{
	this->d = dir;
}

void PinHole::set_zoom(const float z)
{
	this->zoom = z;
}