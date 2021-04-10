#pragma once

#include"Normal.h"
#include"GeometricObject.h"

class Plane:public GeometricObject
{
public:
	Plane(void);//Ĭ�Ϲ��캯��
	
	Plane(const Point3D& p, Normal& n);//���캯��
	~Plane(void);//��������

	/*void set_color(const RGBColor& color);*/
	void set_material(Material* material);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;//����-�����ཻ���Ժ���

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;//��Ӱ����-�����ཻ���Ժ���
public:
	Point3D point;//ƽ�洩���ĵ�
	Normal normal;//ƽ��ķ�ʸ��
	static const double kEpsilon;//��ֵ��С��һ������
};
/*
˵����
1.���ڡ����캯������n����Normal���ã�����const Normal���ã���Ϊ�ڹ��캯������Ҫ���䵥λ��ʱ��Ҫ�ı�n��ֵ��С��
2.��Ϊ�����в�û�д��麯�������Ը��ಢ���ǳ����ࡣ
3.kEpsilon��һ����С��ֵ�����ǲ���Ϊ0����������ĳЩ���⡣
4.������GeometricObject��������࣬�ڹ��캯����Ҳ��Ҫ����������ݳ�Ա���г�ʼ����
*/

