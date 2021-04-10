#include "pch.h"
#include "CRectangle.h"

#include"ShadeRec.h"
#include"Point2D.h"
#include"Sampler.h"
#include"Maths.h"

const double CRectangle::kEpsilon = 0.001;

CRectangle::CRectangle(void)
	:GeometricObject(),p0(-1.0,0.0,-1.0),a(0.0,0.0,1.0),
	b(1.0,0.0,0.0),normal(0.0,1.0,0.0),
	a_len_squared(1.0),b_len_squared(1.0),
	sampler_ptr(nullptr)
{
	inv_area = 1.0 / (a.Length()*b.Length());
}

CRectangle::~CRectangle(void)
{
}

CRectangle::CRectangle(const Point3D & _p0, const Vector3D & _a, const Vector3D & _b)
	:GeometricObject(),p0(_p0),a(_a),b(_b)
{
	normal = a ^ b;
	normal.Normalize();
	this->inv_area = 1.0 / (a.Length()*b.Length());
	this->a_len_squared = a.Length_Square();
	this->b_len_squared = b.Length_Square();
	this->sampler_ptr = nullptr;
}

CRectangle::CRectangle(const Point3D & _p0, const Vector3D & _a, const Vector3D & _b, const Normal & _n)
	:GeometricObject(),p0(_p0),a(_a),b(_b),normal(_n)
{
	this->inv_area = 1.0 / (a.Length()*b.Length());
	this->a_len_squared = a.Length_Square();
	this->b_len_squared = b.Length_Square();
	normal.Normalize();
	this->sampler_ptr = nullptr;
}

void CRectangle::set_sampler(Sampler* sampler)
{
	this->sampler_ptr = sampler;
}

bool CRectangle::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	double t = (p0 - ray.o)*normal / (ray.d*normal);//假设平面无限延伸，光线则与平面必定相交一点

	if (t <= kEpsilon)//如果光线与平面相交保留，如果是光线的反向延长线与平面相交丢弃
		return(false);

	Point3D p = ray.o + t * ray.d;//平面与光线的碰撞点
	Vector3D d = p - p0;//碰撞点与矩形上的一点的向量

	double ddota = d * a;//这里|d|cosθ为d在a上的投影，也可以表示为:(a·b)/|a|=|d|cosθ，其将与|a|比较，为了简单，两边同时乘以|a|,得出【a·b】将与【a²】比较大小

	if (ddota<0.0 || ddota>a_len_squared)
		return(false);

	double ddotb = d * b;

	if (ddotb<0.0 || ddotb>b_len_squared)
		return(false);

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = p;

	return(true);
}

Point3D CRectangle::sample(void)
{
	Point2D sample_point = sampler_ptr->sample_unit_square();
	return(p0 + sample_point.x*a + sample_point.y*b);
}

float CRectangle::pdf(ShadeRec& sr)
{
	return(this->inv_area);
}

Normal CRectangle::get_normal(const Point3D & p)
{
	return(this->normal);
}

void CRectangle::set_material(Material * material_ptr)
{
	this->material = material_ptr;
}

BBox CRectangle::get_bounding_box(void)//根据矩形的大小设计最接近矩形（节约碰撞空间）的包围盒体
{
	double delta = 0.0001;

	return(BBox(Min(p0.x, p0.x + a.x + b.x) - delta, Max(p0.x, p0.x + a.x + b.x) + delta,
		Min(p0.y, p0.y + a.y + b.y) - delta, Max(p0.y, p0.y + a.y + b.y) + delta,
		Min(p0.z, p0.z + a.z + b.z) - delta, Max(p0.z, p0.z + a.z + b.z) + delta));
}

/*bool CRectangle::set_shadows(const bool a)
{
	return(shadows);
}*/