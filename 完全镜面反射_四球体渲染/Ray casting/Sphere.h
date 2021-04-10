#pragma once

#include"GeometricObject.h"
#include"ShadeRec.h"
#include"Sampler.h"

class Sphere:public GeometricObject
{
public:
	Sphere(void);//Ĭ�Ϲ��캯��
	
	Sphere(const Point3D& _center, const double _radius);//���캯��
	
	~Sphere(void);//��������

	void set_sampler(Sampler* _sampler);

	virtual Point3D sample(void);

	virtual float pdf(ShadeRec& sr);

	virtual Normal get_normal(const Point3D& p);

	void set_center(const Point3D& p);//������������
	
	void set_radius(const double r);//��������뾶
	//void set_color(const RGBColor& color);//����������ɫ
	
	void set_material(Material* material);//�����������

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;//����-�����ཻ���Ժ���
	
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;//��Ӱ����-�����ཻ���Ժ���

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

public:
	double radius;//����뾶
	Point3D center;//��������
	Normal normal;
	Sampler* sampler_ptr;
	float inv_area;
	BBox bbox;//��Χ��
	static const double kEpsilon;
};
/*
˵����
1.����ΪGeometricObject��������࣬��Ҫ�Ի������ݳ�Ա���г�ʼ����
2.�ڹ���-�����ཻ���Ժ����з�ʸ���ļ�����Ŀǰ��û�������á�
*/