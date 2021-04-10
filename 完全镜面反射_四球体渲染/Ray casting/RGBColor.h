#pragma once

class RGBColor
{
public:
	RGBColor(void);//默认构造函数
	RGBColor(const double a);//构造函数
	RGBColor(const double _r, const double _g, const double _b);//构造函数
	RGBColor(const RGBColor& rhs);//拷贝构造函数
	~RGBColor(void);//析构函数
	RGBColor operator+(const RGBColor& c)const;//(颜色值+颜色值)
	friend RGBColor operator*(const double a, const RGBColor& c);//(常数*颜色值)
	//RGBColor operator*(const double a)const;//（颜色值*常数）
	RGBColor operator/(const double a)const;//（颜色值/常数）
	RGBColor& operator/=(const double a);//（颜色值/=常数）
	RGBColor& operator=(const RGBColor& c);//（颜色值=颜色值）
	RGBColor operator*(const RGBColor& c);//（颜色值*颜色值）
	RGBColor& operator*=(const float a);//(颜色值*常数)
	RGBColor powc(float p)const;//（颜色值的幂）
	RGBColor& operator+=(const RGBColor& c);//（颜色值+=颜色值）
	
public:
	double r, g, b;
};
/*
说明：
1.一个形参的构造函数其作用是便于RGBColor类型数据的声明（可参考GeometricObject类的默认构造函数声明）。
2.powc(p)函数用于进行颜色值的伽马值矫正。
3.注释掉一个重载函数是因为：其会与其他函数引发歧义：两个重载具有相似的转换。
*/