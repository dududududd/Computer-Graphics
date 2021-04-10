#pragma once

#include"CMesh.h"
#include"Point3D.h"
#include"Grid.h"

class CBezierPatch:public Grid
{
public:
	CBezierPatch(void);
	virtual~CBezierPatch(void);
	void ReadControlPoint(Point3D* CtrPt, int ReNumber);//����16�����Ƶ�͵ݹ����
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;
private:
	void SetCurvedPatch(void);//��������
	void Recursion(int ReNumber, CMesh Mesh);//�ݹ麯��
	void Tessellation(CMesh Mesh, Point3D* P, Vector3D* N);//ϸ�ֺ���
	void LeftMultiplyMatrix(double M[4][4], Point3D P[4][4]);//��˶������
	void RightMultiplyMatrix(Point3D P[4][4], double M[4][4]);//�ҳ˶������
	void TransposeMatrix(double M[4][4]);//ת�þ���
private:
	int ReNumber;//�ݹ����
	Point3D CtrPt[16];//�����16�����Ƶ�
};