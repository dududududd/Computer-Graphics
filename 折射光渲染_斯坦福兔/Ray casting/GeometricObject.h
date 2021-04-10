#pragma once

#include"Ray.h"
class ShadeRec;
class Material;
#include"Normal.h"

#include"BBox.h"

class GeometricObject
{
public:
	GeometricObject(void);//Ĭ�Ϲ��캯��

	GeometricObject(const GeometricObject& object);//�������캯��
	
	GeometricObject& operator=(const GeometricObject& geometricobject);//��ֵ���������
	
	virtual~GeometricObject(void);//����������
	
	//RGBColor get_color(void);
	
	Material* get_material(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const = 0;//����-�����ཻ���Ժ���(���麯��)
	
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;//��Ӱ����-�����ཻ���Ժ���
	
	virtual Point3D sample(void);

	virtual float pdf(ShadeRec& sr);

	virtual Normal get_normal(const Point3D& p);

	virtual Normal get_normal(void) const;

	virtual void set_material(Material* material_ptr);

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

	virtual void add_object(GeometricObject* object_ptr);

public:
	//RGBColor color;//��ɫ�ֶ�
	mutable Material* material;//����ָ��
	bool shadows;//�������ö�����Ӱѡ��
};
/*
˵����
1.�ڸ����У����������캯�����͡���ֵ��������ء��ǿ���ʡ�Եģ���Ϊ���ݳ�Ա��û��ָ�������ǳ�����������ָ�����ҡ�
2.������Ϊ���ζ���Ļ��࣬����������������Ϊ��������������Ϊ��������������������ʱ������ָ���ָ�������ಢ�����������������ͷ�ȫ���ڴ棻������������ʱֻ����û����������������ڴ��ͷŲ���ȫ��
3.�������ݳ�Ա��Ŀǰ�����漰���յļ��㣬���Բ���RGBColor�ֶ������档
4.��Ϊ�Ǽ̳нṹ�����Խ����ݳ�Ա�ķ�����������Ϊ������
5.����Ϊ�����࣬����Թ���-�����ཻ���Ժ�������ʵ�֡�
*/