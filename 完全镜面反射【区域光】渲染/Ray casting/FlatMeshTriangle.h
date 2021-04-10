#pragma once

#include"MeshTriangle.h"

class FlatMeshTriangle:public MeshTriangle
{
public:
	
	FlatMeshTriangle(void);

	FlatMeshTriangle(Mesh* _meshptr, const int _index0, const int _index1, const int _index2);

	FlatMeshTriangle(const FlatMeshTriangle& fmt);

	FlatMeshTriangle& operator=(const FlatMeshTriangle& rhs);

	virtual~FlatMeshTriangle(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;
};
/*
//FlatMeshTriangle��ʹ�þ��к㶨���ߵ�ƽ����ɫ������������
//�⽫ʹ�ô�MeshTriangle�̳е���Ӱ���к���
*/