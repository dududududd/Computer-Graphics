#include "pch.h"
#include "FlatMeshTriangle.h"

#include"Constants.h"
#include"World.h"

FlatMeshTriangle::FlatMeshTriangle(void)
	:MeshTriangle()
{
}

FlatMeshTriangle::FlatMeshTriangle(Mesh * _meshptr, const int _index0, const int _index1, const int _index2)
	: MeshTriangle(_meshptr, _index0, _index1, _index2)
{

}

FlatMeshTriangle::FlatMeshTriangle(const FlatMeshTriangle & fmt)
	:MeshTriangle(fmt)
{
}

FlatMeshTriangle & FlatMeshTriangle::operator=(const FlatMeshTriangle & rhs)
{
	if (this == &rhs)
		return(*this);
	else
	{
		MeshTriangle::operator=(rhs);

		return(*this);
	}
}

FlatMeshTriangle::~FlatMeshTriangle(void)
{
}

bool FlatMeshTriangle::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	Point3D v0(mesh_ptr->vertices[index0]);
	Point3D v1(mesh_ptr->vertices[index1]);
	Point3D v2(mesh_ptr->vertices[index2]);

	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return (false);

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return (false);

	tmin = t;
	sr.normal = normal;  				//为了平面着色
	sr.local_hit_point = ray.o + t * ray.d;//为了纹理映射

	return (true);
}
