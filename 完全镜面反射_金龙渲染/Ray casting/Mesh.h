#pragma once

#include<vector>
#include"Point3D.h"
#include"Normal.h"

class Mesh
{
public:
	Mesh(void);

	virtual~Mesh(void);

public:

	std::vector<Point3D>vertices;//顶点
	std::vector<int>indices;//顶点索引
	std::vector<Normal>normals;//每个顶点的平均法矢量
	std::vector<std::vector<int>>vertex_faces;//每个顶点共享的面
	std::vector<float>u;//每个顶点的u纹理坐标
	std::vector<float>v;//每个顶点的v纹理坐标
	int num_vertices;//顶点数
	int num_triangles;//三角形数
};

