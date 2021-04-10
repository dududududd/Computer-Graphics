#include "CBezierPatch.h"

#include"SmoothTriangle.h"

CBezierPatch::CBezierPatch(void)
{
	ReNumber = 0;
}

CBezierPatch::~CBezierPatch(void)
{
}

void CBezierPatch::ReadControlPoint(Point3D * CtrPt, int ReNumber)
{
	for (int i = 0; i < 16; i++)
		this->CtrPt[i] = CtrPt[i];
	this->ReNumber = ReNumber;
	SetCurvedPatch();
}

void CBezierPatch::SetCurvedPatch(void)
{
	CMesh Mesh;
	Mesh.BL = CT2(0, 0), Mesh.BR = CT2(1, 0);//初始化uv
	Mesh.TR = CT2(1, 1), Mesh.TL = CT2(0, 1);
	Recursion(ReNumber, Mesh);//递归函数
}

bool CBezierPatch::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	return(Grid::hit(ray, tmin, sr));
}

bool CBezierPatch::shadow_hit(const Ray & ray, float & tmin) const
{
	return (Grid::shadow_hit(ray, tmin));
}

void CBezierPatch::Recursion(int ReNumber, CMesh Mesh)
{
	if (0 == ReNumber)
	{
		Point3D P[4];////四边形平面网格顶点
		Vector3D N[4];//顶点法向量
		Tessellation(Mesh, P, N);//细分曲面，将（u，v）点转换为（x，y）点
		return;
	}
	else
	{
		CT2 Mid = (Mesh.BL + Mesh.TR) / 2.0;
		CMesh SubMesh[4];//一分为四个
		//左下子长方形
		SubMesh[0].BL = Mesh.BL;
		SubMesh[0].BR = CT2(Mid.u, Mesh.BL.v);
		SubMesh[0].TR = CT2(Mid.u, Mid.v);
		SubMesh[0].TL = CT2(Mesh.BL.u, Mid.v);
		//右下子长方形
		SubMesh[1].BL = SubMesh[0].BR;
		SubMesh[1].BR = Mesh.BR;
		SubMesh[1].TR = CT2(Mesh.BR.u, Mid.v);
		SubMesh[1].TL = SubMesh[0].TR;
		//右上子长方形
		SubMesh[2].BL = SubMesh[1].TL;
		SubMesh[2].BR = SubMesh[1].TR;
		SubMesh[2].TR = Mesh.TR;
		SubMesh[2].TL = CT2(Mid.u, Mesh.TR.v);
		//左上子长方形
		SubMesh[3].BL = SubMesh[0].TL;
		SubMesh[3].BR = SubMesh[2].BL;
		SubMesh[3].TR = SubMesh[2].TL;
		SubMesh[3].TL = Mesh.TL;
		Recursion(ReNumber - 1, SubMesh[0]);//递归绘制4个子曲面
		Recursion(ReNumber - 1, SubMesh[1]);
		Recursion(ReNumber - 1, SubMesh[2]);
		Recursion(ReNumber - 1, SubMesh[3]);
	}
}

void CBezierPatch::Tessellation(CMesh Mesh, Point3D * P, Vector3D * N)
{
	double M[4][4];//系数矩阵M
	M[0][0] = -1, M[0][1] = 3, M[0][2] = -3,M[0][3] = 1;
	M[1][0] = 3,  M[1][1] = -6,M[1][2] = 3, M[1][3] = 0;
	M[2][0] = -3, M[2][1] = 3, M[2][2] = 0, M[2][3] = 0;
	M[3][0] = 1,  M[3][1] = 0, M[3][2] = 0, M[3][3] = 0;
	Point3D P3[4][4];//曲线计算用控制点数组
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			P3[i][j] = CtrPt[i * 4 + j];
	LeftMultiplyMatrix(M, P3);//系数矩阵左乘三维点矩阵
	TransposeMatrix(M);//计算转置矩阵
	RightMultiplyMatrix(P3, M);//系数矩阵右乘三维点矩阵
	double u0, u1, u2, u3, v0, v1, v2, v3;//u，v参数的幂
	double u[4] = { Mesh.BL.u,Mesh.BR.u ,Mesh.TR.u ,Mesh.TL.u };
	double v[4] = { Mesh.BL.v,Mesh.BR.v ,Mesh.TR.v ,Mesh.TL.v };
	for (int i = 0; i < 4; i++)
	{
		u3 = pow(u[i], 3.0), u2 = pow(u[i], 2.0), u1 = u[i], u0 = 1;
		v3 = pow(v[i], 3.0), v2 = pow(v[i], 2.0), v1 = v[i], v0 = 1;
		P[i] = (u3 * P3[0][0] + u2 * P3[1][0] + u1 * P3[2][0] + u0 * P3[3][0]) * v3
			+ (u3 * P3[0][1] + u2 * P3[1][1] + u1 * P3[2][1] + u0 * P3[3][1]) * v2
			+ (u3 * P3[0][2] + u2 * P3[1][2] + u1 * P3[2][2] + u0 * P3[3][2]) * v1
			+ (u3 * P3[0][3] + u2 * P3[1][3] + u1 * P3[2][3] + u0 * P3[3][3]) * v0;
		//计算顶点法向量
		Point3D uTagent, vTagent;
		double du3, du2, du1, du0;
		du3 = 3.0 * pow(u[i], 2.0), du2 = 2.0 * u[i], du1 = 1, du0 = 0.0;
		v3 = pow(v[i], 3.0), v2 = pow(v[i], 2.0), v1 = v[i], v0 = 1.0;
		uTagent = (du3 * P3[0][0] + du2 * P3[1][0] + du1 * P3[2][0] + du0 * P3[3][0]) * v3
			+ (du3 * P3[0][1] + du2 * P3[1][1] + du1 * P3[2][1] + du0 * P3[3][1]) * v2
			+ (du3 * P3[0][2] + du2 * P3[1][2] + du1 * P3[2][2] + du0 * P3[3][2]) * v1
			+ (du3 * P3[0][3] + du2 * P3[1][3] + du1 * P3[2][3] + du0 * P3[3][3]) * v0;

		double dv3, dv2, dv1, dv0;
		u3 = pow(u[i], 3.0), u2 = pow(u[i], 2.0), u1 = u[i], u0 = 1.0;
		dv3 = 3.0 * pow(v[i], 2.0), dv2 = 2.0 * v[i], dv1 = 1.0, dv0 = 0.0;
		vTagent = (u3 * P3[0][0] + u2 * P3[1][0] + u1 * P3[2][0] + u0 * P3[3][0]) * dv3
			+ (u3 * P3[0][1] + u2 * P3[1][1] + u1 * P3[2][1] + u0 * P3[3][1]) * dv2
			+ (u3 * P3[0][2] + u2 * P3[1][2] + u1 * P3[2][2] + u0 * P3[3][2]) * dv1
			+ (u3 * P3[0][3] + u2 * P3[1][3] + u1 * P3[2][3] + u0 * P3[3][3]) * dv0;
		N[i] = (Vector3D(uTagent) ^ Vector3D(vTagent));
		N[i].Normalize();//规范化顶点法向量
		Vector3D Pu = Vector3D(uTagent), Pv = Vector3D(vTagent);
		if (Pv.Length() < 1e-4)
		{
			N[i] = Vector3D(P[i]);
			N[i].Normalize();
		}//南北极点的V向偏导数为零
			
			
		if (Pu.Length() < 1e-4)
		{
			N[i] = Vector3D(P[i]);
			N[i].Normalize();
		}//南北极点的U向偏导数为零
	}
	SmoothTriangle* triangle_ptr1 = new SmoothTriangle(P[0], P[1], P[2]);
	triangle_ptr1->n0 = N[0];
	triangle_ptr1->n1 = N[1];
	triangle_ptr1->n2 = N[2];
	objects.push_back(triangle_ptr1);
	SmoothTriangle* triangle_ptr2 = new SmoothTriangle(P[0], P[2], P[3]);
	triangle_ptr2->n0 = N[0];
	triangle_ptr2->n1 = N[2];
	triangle_ptr2->n2 = N[3];
	objects.push_back(triangle_ptr2);
}

void CBezierPatch::LeftMultiplyMatrix(double M[4][4], Point3D P[4][4])
{
	Point3D PTemp[4][4];//临时矩阵
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			PTemp[i][j] = M[i][0] * P[0][j] + M[i][1] * P[1][j] + M[i][2] * P[2][j] + M[i][3] * P[3][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			P[i][j] = PTemp[i][j];
}

void CBezierPatch::RightMultiplyMatrix(Point3D P[4][4], double M[4][4])
{
	Point3D PTemp[4][4];//临时矩阵
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			PTemp[i][j] = P[i][0] * M[0][j] + P[i][1] * M[1][j] + P[i][2] * M[2][j] + P[i][3] * M[3][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			P[i][j] = PTemp[i][j];
}

void CBezierPatch::TransposeMatrix(double M[4][4])
{
	double PTemp[4][4];//临时矩阵
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			PTemp[j][i] = M[i][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			M[i][j] = PTemp[i][j];
}
