#pragma once

#include"Matrix.h"
class Point3D;
class Normal;

class Vector3D
{
public:
	Vector3D(void);//Ĭ�Ϲ��캯��
	Vector3D(const Vector3D& rhs);//�������캯��
	Vector3D(const Point3D& p);//�������캯��
	Vector3D(const Normal& n);//�������캯��
	Vector3D(const double a);//���캯��
	Vector3D(const double _x, const double _y, const double _z);//���캯��
	~Vector3D(void);//��������

	Vector3D operator+(const Vector3D& v)const;//(����+����)
	Vector3D operator-(const Vector3D& v)const;//(����-����)

	float distance(const Point3D& p)const;//����������ά��ľ��룩

	friend Vector3D operator*(const double a, const Vector3D& v);//������*������
	Vector3D operator*(const double a)const;//������*������
	
	Vector3D operator/(const double a)const;//(����/����)

	Vector3D& operator=(const Vector3D& v);//������=������
	Vector3D& operator=(const Normal& n);//������=��ʸ����

	double Length(void);//�����ĳ���
	double Length_Square(void)const;//�����ĳ��ȵ�ƽ��

	double operator*(const Vector3D& v)const;//�������ĵ����
	Vector3D operator^(const Vector3D& v)const;//�������Ĳ����

	Vector3D operator-(void)const;//��������ȡ����
	Vector3D& operator+=(const Vector3D& v);//������+=������

	Vector3D& hat(void);//�����ķ�������������������һ��������
	void Normalize(void);//�����ķ���������������һ��������

	friend Vector3D operator*(const Matrix& mat, const Vector3D& v);//��4*4������������ˣ�
public:
	double x, y, z;
};
/*
˵����
1.�β�Ϊһ�������Ĺ��캯����Ϊ�˱���Vector3D���͵����ݱ����ĳ�ʼ��(�ɲο�Ray������ݳ�Աd�Ĺ��캯�����塣)
2.��������ΪPoint3D���͵Ŀ������캯������������Ϊ�˽��������������ʵ�֡�
3.����4*4������������ˣ����ǿ���ƽ�ƶ�������˵�������õģ����Կ��Խ����Ϊ3*3�������ά�����ˡ�
4.Vector3D operator*(const Matrix& mat, const Vector3D& v)��������ʵ�ֹ��߷����еķ�������d����任������
dx'=m00*dx+m01*dy+m02*dz
dy'=m10*dx+m11*dy+m12*dz
dz'=m20*dx+m21*dy+m22*dz
*/