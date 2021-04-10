#include "pch.h"
#include "MeshTriangle.h"

#include"Constants.h"
#include"Maths.h"

MeshTriangle::MeshTriangle(void)
	:GeometricObject(), mesh_ptr(nullptr),
	index0(0), index1(0), index2(0),
	normal()
{

}

MeshTriangle::MeshTriangle(const MeshTriangle & meshtriangle)
	:GeometricObject(), mesh_ptr(meshtriangle.mesh_ptr),
	index0(meshtriangle.index0), index1(meshtriangle.index1), index2(meshtriangle.index2),
	normal(meshtriangle.normal)
{

}

MeshTriangle & MeshTriangle::operator=(const MeshTriangle & rhs)
{
	if (this == &rhs)
		return(*this);
	else
	{
		this->mesh_ptr = rhs.mesh_ptr;
		this->index0 = rhs.index0;
		this->index1 = rhs.index1;
		this->index2 = rhs.index2;
		this->normal = rhs.normal;
		
		return(*this);
	}
}

//法线在Grid:：read_ply_文件中计算
MeshTriangle::MeshTriangle(Mesh * _mesh_ptr, const int _index0, const int _index1, const int _index2)
	:GeometricObject(), mesh_ptr(_mesh_ptr),
	index0(_index0), index1(_index1), index2(_index2)
{

}

MeshTriangle::~MeshTriangle(void)
{
	if (mesh_ptr)
	{
		/*delete mesh_ptr;
		mesh_ptr = nullptr;*/
	}
}

//此函数独立于导出的三角形类型：
//平坦，平滑，平坦的uv，平滑的uv
bool MeshTriangle::shadow_hit(const Ray & ray, float & tmin) const
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

	double r = r = e * l - h * i;
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

	return (true);
}

void MeshTriangle::compute_normal(const bool reverse_normal)
{
	normal = (mesh_ptr->vertices[index1] - mesh_ptr->vertices[index0])^(mesh_ptr->vertices[index2] - mesh_ptr->vertices[index0]);

	normal.Normalize();

	if (reverse_normal)
		normal = -normal;
}

//这在Grid:：compute_mesh_normals中被调用
Normal MeshTriangle::get_normal(void) const
{
	return (this->normal);
}

BBox MeshTriangle::get_bounding_box(void)
{
	double delta = 0.0001;////避免边界框退化

	Point3D v1(mesh_ptr->vertices[index0]);
	Point3D v2(mesh_ptr->vertices[index1]);
	Point3D v3(mesh_ptr->vertices[index2]);

	return(BBox(Min(Min(v1.x, v2.x), v3.x) - delta, Max(Max(v1.x, v2.x), v3.x) + delta,
		Min(Min(v1.y, v2.y), v3.y) - delta, Max(Max(v1.y, v2.y), v3.y) + delta,
		Min(Min(v1.z, v2.z), v3.z) - delta, Max(Max(v1.z, v2.z), v3.z) + delta));
}

//用于纹理映射
float MeshTriangle::interpolate_u(const float beta, const float gamma) const
{
	return((1 - beta - gamma) * mesh_ptr->u[index0]
		+ beta * mesh_ptr->u[index1]
		+ gamma * mesh_ptr->u[index2]);
}

//用于纹理映射
float MeshTriangle::interpolate_v(const float beta, const float gamma) const
{
	return((1 - beta - gamma) * mesh_ptr->v[index0]
		+ beta * mesh_ptr->v[index1]
		+ gamma * mesh_ptr->v[index2]);
}
