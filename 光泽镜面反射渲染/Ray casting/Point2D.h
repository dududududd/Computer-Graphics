#pragma once

class Point2D
{
public:
	Point2D(void);//默认构造函数
	Point2D(const double arg);//构造函数
	Point2D(const double _x, const double _y);//构造函数
	Point2D(const Point2D& p);//拷贝构造函数

	~Point2D(void);//析构函数

	Point2D& operator=(const Point2D& rhs);//赋值运算符重载
	Point2D operator*(const double a);//乘法运算符重载
public:
	double x, y;//X坐标，Y坐标
};
/*
说明：
1.在该类中，为了便于进行二维点坐标初始化，所以分别声明了单一参数和两个参数的构造函数。
2.在编写该类时，并未将该类与Point3D类实现继承关系，所以析构函数不必声明为虚函数。
3.在该类中，数据成员中并未有指针类型变量，所以【拷贝构造函数】和【赋值运算符重载】不是必要的。
*/