#pragma once

class RGBColor
{
public:
	RGBColor(void);//Ĭ�Ϲ��캯��
	RGBColor(const double a);//���캯��
	RGBColor(const double _r, const double _g, const double _b);//���캯��
	RGBColor(const RGBColor& rhs);//�������캯��
	~RGBColor(void);//��������
	RGBColor operator+(const RGBColor& c)const;//(��ɫֵ+��ɫֵ)
	friend RGBColor operator*(const double a, const RGBColor& c);//(����*��ɫֵ)
	//RGBColor operator*(const double a)const;//����ɫֵ*������
	RGBColor operator/(const double a)const;//����ɫֵ/������
	RGBColor& operator/=(const double a);//����ɫֵ/=������
	RGBColor& operator=(const RGBColor& c);//����ɫֵ=��ɫֵ��
	RGBColor operator*(const RGBColor& c);//����ɫֵ*��ɫֵ��
	RGBColor& operator*=(const float a);//(��ɫֵ*����)
	RGBColor powc(float p)const;//����ɫֵ���ݣ�
	RGBColor& operator+=(const RGBColor& c);//����ɫֵ+=��ɫֵ��
	
public:
	double r, g, b;
};
/*
˵����
1.һ���βεĹ��캯���������Ǳ���RGBColor�������ݵ��������ɲο�GeometricObject���Ĭ�Ϲ��캯����������
2.powc(p)�������ڽ�����ɫֵ��٤��ֵ������
3.ע�͵�һ�����غ�������Ϊ����������������������壺�������ؾ������Ƶ�ת����
*/