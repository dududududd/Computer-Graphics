#pragma once

#include"GeometricObject.h"
#include"Sampler.h"

class CRectangle:public GeometricObject
{
public:

	CRectangle(void);

	~CRectangle(void);

	CRectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b);

	CRectangle(const Point3D& _p0, const Vector3D& _a, const Vector3D& _b, const Normal& _n);

	virtual void set_sampler(Sampler* sampler);//���ò�����ָ��

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;//����-�����ཻ���Ժ���

	virtual Point3D sample(void);//����λ�������ϵĲ�����ӳ�䵽������

	virtual float pdf(ShadeRec& sr);//��þ����ϵĲ���������ܶȺ������������Ϊ��ø�������ĸ�����ͬ

	virtual Normal get_normal(const Point3D& p);//��þ��εķ�ʸ���������ϵĵ�ķ�ʸ��������ͬ�����Ѿ��ھ��ζ���ʱ���ã�

	void set_material(Material* material_ptr);//���ö������

	virtual BBox get_bounding_box(void);

private:

	Point3D p0;//��ȡ�ĵ�λ�������ϵĲ�����
	Vector3D a;//���α�����(��Ϊ��λ����)
	Vector3D b;//���α�����(��Ϊ��λ����)
	double a_len_squared;//�߳�a��ƽ��
	double b_len_squared;//�߳�b��ƽ��
	Normal normal;//������ķ�ʸ��
	Sampler* sampler_ptr;//������ָ��
	float inv_area;//������ĵ���
	static const double kEpsilon;//һ����Сֵ
};