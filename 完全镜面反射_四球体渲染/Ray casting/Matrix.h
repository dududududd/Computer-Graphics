#pragma once
class Matrix
{
public:
	Matrix(void);//Ĭ�Ϲ��캯��
	Matrix(const Matrix& mat);//�������캯��

	~Matrix(void);//��������

	Matrix& operator=(const Matrix& rhs);//��ֵ���������
	Matrix operator*(const Matrix& mat)const;//�˷����������(����˷�)
	Matrix operator/(const double d);//�������������
	void set_identity(void);//����Ϊ��λ����

public:
	double m[4][4];
};
/*
˵����
1.�������ڴ洢����Ԫ�ء�
*/

