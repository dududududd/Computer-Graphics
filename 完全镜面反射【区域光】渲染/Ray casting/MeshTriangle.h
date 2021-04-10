#pragma once

#include"Mesh.h"
#include"GeometricObject.h"

class MeshTriangle:public GeometricObject
{
public:
	MeshTriangle(void);

	MeshTriangle(const MeshTriangle& meshtriangle);

	MeshTriangle& operator=(const MeshTriangle& rhs);

	MeshTriangle(Mesh* _mesh_ptr, const int _index0, const int _index1, const int _index2);

	virtual~MeshTriangle(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const = 0;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

	void compute_normal(const bool reverse_normal);//计算面法矢量

	virtual Normal get_normal(void)const;

	virtual BBox get_bounding_box(void);

protected:

	float interpolate_u(const float beta, const float gamma)const;

	float interpolate_v(const float beta, const float gamma)const;

public:
	Mesh* mesh_ptr;//存储所有数据
	int index0, index1, index2;//索引到网格中的顶点数组
	Normal normal;
	float area;//半透明所需
};

/*
//从MeshTriangle派生的三角形类，例如FlatMeshTriangle和SmoothMeshTriangle，
//存储在用于渲染三角形网格的规则网格中
//网格三角形将整数索引存储到网格对象的顶点数组中
//网格三角形还存储指向网格对象的指针
//网格三角形还存储法线，用于平坦网格三角形和
//计算平滑网格三角形每个顶点的平均法线
//网格三角形定义阴影命中函数，因为这与
//三角形是平面着色或平滑着色或uv贴图或非uv贴图
*/