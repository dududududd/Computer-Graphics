#pragma once

#include"Vector3D.h"
#include"Matrix.h"

class Point3D
{
public:
	Point3D(void);//Ĭ�Ϲ��캯��
	Point3D(const Point3D& rhs);//�������캯��
	Point3D(const double a);//���캯��
	Point3D(const double _x, const double _y, const double _z);//���캯��
	~Point3D(void);//��������

	Point3D operator+(const Vector3D& u)const;//(����+����)
	Point3D operator-(const Vector3D& u)const;//(����-����)
	Vector3D operator-(const Point3D& p)const;//(����-����)

	double Distance_Square(const Point3D& p)const;//����֮������ƽ��
	double Distance(const Point3D& p)const;//����֮��ľ���
	
	float distance(const Vector3D& v)const;

	Point3D& operator=(const Point3D& p);//������=���㣩
	Point3D operator*(const double a)const;//������*������
	friend Point3D operator*(const double a, const Point3D& p);//������*���㣩

	friend Point3D operator*(const Matrix& mat, const Point3D& p);//��4*4������˶��㣩
	
public:
	double x, y, z;
};
/*
˵����
1.����Ϊһ�������Ĺ��캯����Ϊ�˱���Point3D���͵����ݱ����ĳ�ʼ��(�����ɲο�Ray������ݳ�Աo�Ĺ��캯������)��
2.����Ϊ���������Ĺ��캯����Ϊ�˷���ֵ��������double������ת��Ϊһ��Point3D���͵����ݣ��ɲο���������������صĶ��壩��
3.������������ز�֧�ֶ�����������Խ�������Ϊ��Ԫ������
4.����4*4������˶��㣬���Ƚ�����������껯֮����еĳ˷����㡣
5.����Point3D operator*(const Matrix& mat, const Point3D& p)�������ڶ�������ֻ�Ǳ�ʾ��Point3D��������4D���㣬
������������ʵ�ֹ���ԭ��o����任������
��:
ox'=m00*ox+m01*oy+m02*oz+m03
oy'=m10*ox+m11*oy+m12*oz+m13
oz'=m20*ox+m21*oy+m22*oz+m23
*/