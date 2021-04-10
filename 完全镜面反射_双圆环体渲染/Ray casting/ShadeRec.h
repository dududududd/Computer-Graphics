#pragma once

#include"Normal.h"
#include"RGBColor.h"

#include"Ray.h"
#include"Material.h"
class World;

class ShadeRec
{
public:
	ShadeRec(World& wr);//���캯��������ShadeRec���Ĭ�Ϲ��캯��
	
	ShadeRec(const ShadeRec& sr);//�������캯��
	~ShadeRec(void);//��������
	
	ShadeRec& operator=(const ShadeRec& rhs);//��ֵ���������
public:
	bool hit_an_object;//�����Ƿ����������ײ
	Material* material_ptr;//�������Ĳ���
	Point3D hit_point;//���е����������
	Point3D local_hit_point;//���ڽ������ӵ�����
	Normal normal;//��ײ��ķ�ʸ��
	RGBColor color;//��ɫ
	Ray ray;//���ھ���߹�
	int depth;//�ݹ����
	Vector3D dir;//�����������
	double t;//ʸ������

	World& w;//World������
};
/*
˵����
1.��������Ϊһ�������࣬�����洢���߸����������ȫ����Ϣ��
2.����ġ��������캯�����͡���ֵ��������ء����Ǳ���ġ�
3.ShadeRec(World& wr)���ڵļ�ֵ��ʹ��������ShadeRec�Դ���Ĭ�Ϲ��캯������Ϊ�����á�����Ϊ�գ�����ShadeRec��Ϊһ���м��࣬����Ҫʹ��ָ��������ֵ�Ĵ��ݵġ�
*/