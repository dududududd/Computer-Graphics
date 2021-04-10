#pragma once

#include"MeshTriangle.h"

class SmoothMeshTriangle:public MeshTriangle
{
public:

	SmoothMeshTriangle(void);

	SmoothMeshTriangle(Mesh* _meshptr, const int _index0, const int _index1, const int _index2);

	SmoothMeshTriangle(const SmoothMeshTriangle& fmt);

	SmoothMeshTriangle& operator= (const SmoothMeshTriangle& rhs);

	virtual~SmoothMeshTriangle(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

protected:

	Normal interpolate_normal(const float beta, const float gamma)const;//����㷨ʸ��
};
/*
//SmoothMeshTriangle��һ�����������Σ�����ÿ�����е�ʹ��ƽ����ɫ�Ͳ�ֵ����
*/
