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

	std::vector<Point3D>vertices;//����
	std::vector<int>indices;//��������
	std::vector<Normal>normals;//ÿ�������ƽ����ʸ��
	std::vector<std::vector<int>>vertex_faces;//ÿ�����㹲�����
	std::vector<float>u;//ÿ�������u��������
	std::vector<float>v;//ÿ�������v��������
	int num_vertices;//������
	int num_triangles;//��������
};

