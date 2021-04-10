#pragma once

#include"Vector3D.h"
class ShadeRec;
#include"RGBColor.h"
#include"Ray.h"

class Light
{
public:
	Light(void);

	virtual~Light(void);

	virtual Vector3D get_direction(ShadeRec& sr) = 0;

	virtual RGBColor L(ShadeRec& sr) = 0;

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const = 0;//��ײ���Ƿ�����Ӱ֮��

	virtual bool casts_shadows();//�Ƿ�����Ӱ����Ͷ��

	virtual float G(const ShadeRec& sr)const;

	virtual float pdf(ShadeRec& sr);

public:
	bool shadows;//��Ӱ
};
/*
˵����
1.get_direction()����������ײ�㴦�Ĺ��߷���
2.L()����������ײ�㴦����������
3.����ls��color��δ�����ڻ����е�ԭ�������������Լ��������գ�ls()����λ�ڶ�Ӧ������ʹ�õķ�������С�
������ս����������������ɫֵ������λ�õı仯��
*/

