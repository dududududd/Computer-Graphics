#pragma once

#include"Vector3D.h"
#include"Matrix.h"

class Normal
{
public:
	Normal(void);//Ĭ�Ϲ��캯��
	Normal(const Normal& rhs);//�������캯��
	Normal(const Vector3D& rhs);//�������캯��
	Normal(const double _x, const double _y, const double _z);//���캯��
	~Normal(void);//��������

	Normal operator-(void)const;//������ȡ��
	Normal operator+(const Normal& m)const;//(������+������)
	double operator*(const Vector3D& u)const;//��������*������
	friend double operator*(const Vector3D& u, const Normal& n);//������*��������

	Normal operator*(const double a)const;//(������*����)
	friend Normal operator*(const double a, const Normal& n);//(����*������)
	
	Vector3D operator+(const Vector3D& u)const;//(������+����)
	friend Vector3D operator+(const Vector3D& u, const Normal& n);//������+��������
	
	Normal& operator=(const Normal& m);//��������=��������
	Normal& operator=(const Vector3D& v);//(������=����)
	Normal& operator=(const Point3D& p);//(������=����)
	Normal& operator+=(const Normal& m);//��������+=��������
	void Normalize(void);//���������ķ���������
	friend Normal operator*(const Matrix& mat, const Normal& n);//�����뷨��������˼���
public:
	double x, y, z;
};
/*
˵����
1.����ΪVector3D���ͱ����Ŀ������캯������Ϊ�˸�ʸ���뷨��=�����������׼��
2.����ΪVectro3D�������͵ı����ĸ�ֵ��������غ������ڽ��в�ͬ���͵�����ת�������ɲο�Sphere��hit�����е�����ת����
3.Normal operator*(const Matrix& mat, const Normal& n)�������ڼ�����任�Ĺ�����ԭ�������ײ��
��Ϊ��
nx'=m00*nx+m10*ny+m20*nz
ny'=m01*nx+m11*ny+m21*nz
nz'=m02*nx+m12*ny+m22*nz
*/