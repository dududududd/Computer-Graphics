#pragma once

#include"Matrix.h"
class Point3D;
class Normal;

class Vector3D
{
public:
	Vector3D(void);//默认构造函数
	Vector3D(const Vector3D& rhs);//拷贝构造函数
	Vector3D(const Point3D& p);//拷贝构造函数
	Vector3D(const Normal& n);//拷贝构造函数
	Vector3D(const double a);//构造函数
	Vector3D(const double _x, const double _y, const double _z);//构造函数
	~Vector3D(void);//析构函数

	Vector3D operator+(const Vector3D& v)const;//(向量+向量)
	Vector3D operator-(const Vector3D& v)const;//(向量-向量)

	float distance(const Point3D& p)const;//（向量与三维点的距离）

	friend Vector3D operator*(const double a, const Vector3D& v);//（常量*向量）
	Vector3D operator*(const double a)const;//（向量*常量）
	
	Vector3D operator/(const double a)const;//(向量/常量)

	Vector3D& operator=(const Vector3D& v);//（向量=向量）
	Vector3D& operator=(const Normal& n);//（向量=法矢量）

	double Length(void);//向量的长度
	double Length_Square(void)const;//向量的长度的平方

	double operator*(const Vector3D& v)const;//（向量的点积）
	Vector3D operator^(const Vector3D& v)const;//（向量的叉积）

	Vector3D operator-(void)const;//（向量的取负）
	Vector3D& operator+=(const Vector3D& v);//（向量+=向量）

	Vector3D& hat(void);//向量的范化（仅操作，不返回一个向量）
	void Normalize(void);//向量的范化（操作并返回一个向量）

	friend Vector3D operator*(const Matrix& mat, const Vector3D& v);//（4*4矩阵与向量左乘）
public:
	double x, y, z;
};
/*
说明：
1.形参为一个变量的构造函数，为了便于Vector3D类型的数据变量的初始化(可参考Ray类的数据成员d的构造函数定义。)
2.参数变量为Point3D类型的拷贝构造函数，其作用是为了将矩阵与向量左乘实现。
3.对于4*4矩阵与向量左乘，我们考虑平移对向量来说是无作用的，所以可以将其简化为3*3矩阵和三维点的相乘。
4.Vector3D operator*(const Matrix& mat, const Vector3D& v)其作用是实现光线方程中的方向向量d的逆变换，即：
dx'=m00*dx+m01*dy+m02*dz
dy'=m10*dx+m11*dy+m12*dz
dz'=m20*dx+m21*dy+m22*dz
*/