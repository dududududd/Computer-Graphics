#pragma once

#include"Vector3D.h"
#include"Matrix.h"

class Normal
{
public:
	Normal(void);//默认构造函数
	Normal(const Normal& rhs);//拷贝构造函数
	Normal(const Vector3D& rhs);//拷贝构造函数
	Normal(const double _x, const double _y, const double _z);//构造函数
	~Normal(void);//析构函数

	Normal operator-(void)const;//法向量取负
	Normal operator+(const Normal& m)const;//(法向量+法向量)
	double operator*(const Vector3D& u)const;//（法向量*向量）
	friend double operator*(const Vector3D& u, const Normal& n);//（向量*法向量）

	Normal operator*(const double a)const;//(法向量*参数)
	friend Normal operator*(const double a, const Normal& n);//(参数*法向量)
	
	Vector3D operator+(const Vector3D& u)const;//(法向量+向量)
	friend Vector3D operator+(const Vector3D& u, const Normal& n);//（向量+法向量）
	
	Normal& operator=(const Normal& m);//（法向量=法向量）
	Normal& operator=(const Vector3D& v);//(法向量=向量)
	Normal& operator=(const Point3D& p);//(法向量=顶点)
	Normal& operator+=(const Normal& m);//（法向量+=法向量）
	void Normalize(void);//（法向量的范化操作）
	friend Normal operator*(const Matrix& mat, const Normal& n);//矩阵与法向量的左乘计算
public:
	double x, y, z;
};
/*
说明：
1.参数为Vector3D类型变量的拷贝构造函数，是为了给矢量与法线=运算符重载做准备
2.参数为Vectro3D引用类型的变量的赋值运算符重载函数便于进行不同类型的数据转换。（可参考Sphere的hit函数中的数据转换）
3.Normal operator*(const Matrix& mat, const Normal& n)函数用于计算逆变换的光线与原对象的碰撞点
即为：
nx'=m00*nx+m10*ny+m20*nz
ny'=m01*nx+m11*ny+m21*nz
nz'=m02*nx+m12*ny+m22*nz
*/