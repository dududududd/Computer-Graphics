#pragma once

class Point2D
{
public:
	Point2D(void);//Ĭ�Ϲ��캯��
	Point2D(const double arg);//���캯��
	Point2D(const double _x, const double _y);//���캯��
	Point2D(const Point2D& p);//�������캯��

	~Point2D(void);//��������

	Point2D& operator=(const Point2D& rhs);//��ֵ���������
	Point2D operator*(const double a);//�˷����������
public:
	double x, y;//X���꣬Y����
};
/*
˵����
1.�ڸ����У�Ϊ�˱��ڽ��ж�ά�������ʼ�������Էֱ������˵�һ���������������Ĺ��캯����
2.�ڱ�д����ʱ����δ��������Point3D��ʵ�ּ̳й�ϵ����������������������Ϊ�麯����
3.�ڸ����У����ݳ�Ա�в�δ��ָ�����ͱ��������ԡ��������캯�����͡���ֵ��������ء����Ǳ�Ҫ�ġ�
*/