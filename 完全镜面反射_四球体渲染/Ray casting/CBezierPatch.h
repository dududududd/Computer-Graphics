#pragma once

#include"CMesh.h"
#include"Point3D.h"
#include"Grid.h"

class CBezierPatch:public Grid
{
public:
	CBezierPatch(void);
	virtual~CBezierPatch(void);
	void ReadControlPoint(Point3D* CtrPt, int ReNumber);//读入16个控制点和递归深度
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;
private:
	void SetCurvedPatch(void);//绘制曲面
	void Recursion(int ReNumber, CMesh Mesh);//递归函数
	void Tessellation(CMesh Mesh, Point3D* P, Vector3D* N);//细分函数
	void LeftMultiplyMatrix(double M[4][4], Point3D P[4][4]);//左乘顶点矩阵
	void RightMultiplyMatrix(Point3D P[4][4], double M[4][4]);//右乘顶点矩阵
	void TransposeMatrix(double M[4][4]);//转置矩阵
private:
	int ReNumber;//递归深度
	Point3D CtrPt[16];//曲面的16个控制点
};