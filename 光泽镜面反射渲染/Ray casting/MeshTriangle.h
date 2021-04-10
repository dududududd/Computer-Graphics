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

	void compute_normal(const bool reverse_normal);//�����淨ʸ��

	virtual Normal get_normal(void)const;

	virtual BBox get_bounding_box(void);

protected:

	float interpolate_u(const float beta, const float gamma)const;

	float interpolate_v(const float beta, const float gamma)const;

public:
	Mesh* mesh_ptr;//�洢��������
	int index0, index1, index2;//�����������еĶ�������
	Normal normal;
	float area;//��͸������
};

/*
//��MeshTriangle�������������࣬����FlatMeshTriangle��SmoothMeshTriangle��
//�洢��������Ⱦ����������Ĺ���������
//���������ν����������洢���������Ķ���������
//���������λ��洢ָ����������ָ��
//���������λ��洢���ߣ�����ƽ̹���������κ�
//����ƽ������������ÿ�������ƽ������
//���������ζ�����Ӱ���к�������Ϊ����
//��������ƽ����ɫ��ƽ����ɫ��uv��ͼ���uv��ͼ
*/