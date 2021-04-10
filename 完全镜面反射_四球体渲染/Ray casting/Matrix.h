#pragma once
class Matrix
{
public:
	Matrix(void);//默认构造函数
	Matrix(const Matrix& mat);//拷贝构造函数

	~Matrix(void);//析构函数

	Matrix& operator=(const Matrix& rhs);//赋值运算符重载
	Matrix operator*(const Matrix& mat)const;//乘法运算符重载(矩阵乘法)
	Matrix operator/(const double d);//除法运算符重载
	void set_identity(void);//设置为单位矩阵

public:
	double m[4][4];
};
/*
说明：
1.该类用于存储矩阵元素。
*/

