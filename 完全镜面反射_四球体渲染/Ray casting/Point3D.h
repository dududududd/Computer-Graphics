#pragma once

#include"Vector3D.h"
#include"Matrix.h"

class Point3D
{
public:
	Point3D(void);//默认构造函数
	Point3D(const Point3D& rhs);//拷贝构造函数
	Point3D(const double a);//构造函数
	Point3D(const double _x, const double _y, const double _z);//构造函数
	~Point3D(void);//析构函数

	Point3D operator+(const Vector3D& u)const;//(顶点+向量)
	Point3D operator-(const Vector3D& u)const;//(顶点-向量)
	Vector3D operator-(const Point3D& p)const;//(顶点-顶点)

	double Distance_Square(const Point3D& p)const;//两点之间距离的平方
	double Distance(const Point3D& p)const;//两点之间的距离
	
	float distance(const Vector3D& v)const;

	Point3D& operator=(const Point3D& p);//（顶点=顶点）
	Point3D operator*(const double a)const;//（顶点*常数）
	friend Point3D operator*(const double a, const Point3D& p);//（常数*顶点）

	friend Point3D operator*(const Matrix& mat, const Point3D& p);//（4*4矩阵左乘顶点）
	
public:
	double x, y, z;
};
/*
说明：
1.参数为一个变量的构造函数是为了便于Point3D类型的数据变量的初始化(例：可参考Ray类的数据成员o的构造函数定义)。
2.参数为三个变量的构造函数是为了返回值能由三个double型数据转化为一个Point3D类型的数据（可参考该类中运算符重载的定义）。
3.部分运算符重载不支持多个参数，所以将其声明为友元函数。
4.对于4*4矩阵左乘顶点，是先将顶点其次坐标化之后进行的乘法运算。
5.对于Point3D operator*(const Matrix& mat, const Point3D& p)函数，第二个参数只是表示了Point3D索引而非4D顶点，
其作用是用于实现光线原点o的逆变换操作。
即:
ox'=m00*ox+m01*oy+m02*oz+m03
oy'=m10*ox+m11*oy+m12*oz+m13
oz'=m20*ox+m21*oy+m22*oz+m23
*/